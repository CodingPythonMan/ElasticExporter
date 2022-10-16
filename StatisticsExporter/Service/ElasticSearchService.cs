using Nest;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StatisticsExporter.Service
{
    public class ElasticSearchService
    {
        readonly string FORMAT_INDEX_GAME_LOG = "gamelog_*";

        readonly string Repository = "backup";

        public ElasticClient GetClient(string uri, string indexFormat)
        {
            var settings = new ConnectionSettings(new Uri(uri))
                    .DefaultIndex(indexFormat);

            return new ElasticClient(settings);
        }

        public async Task<bool> RestoreGameLog(string Snapshot)
        {
            ElasticClient client = GetClient(ConfigService._Config.env.elastic, FORMAT_INDEX_GAME_LOG);

            StringBuilder SnapshotSb = new();
            SnapshotSb.Append("curator_");
            DateTime time = DateTime.ParseExact(Snapshot.Substring("gamelog_".Length, "0000.00.00".Length), "yyyy.MM.dd", null);
            SnapshotSb.Append(time.AddDays(1).ToString("yyyy.MM.dd"));

            RestoreDescriptor restoreDescriptor = new RestoreDescriptor(Repository, SnapshotSb.ToString());
            restoreDescriptor.Indices(Snapshot);
            restoreDescriptor.IgnoreUnavailable(true);
            restoreDescriptor.IncludeGlobalState(false);
            restoreDescriptor.WaitForCompletion(true);

            var result = await client.Snapshot.RestoreAsync(restoreDescriptor);

            return result.IsValid;
        }

        public List<string> GetExistLogs(string index)
        {
            ElasticClient client = GetClient(ConfigService._Config.env.elastic, FORMAT_INDEX_GAME_LOG);

            var existIndices = client.Cat.Indices(i => i
                .Index("gamelog_*"));

            var existLogs = existIndices.Records.Select(s => s.Index).ToArray();

            Array.Sort(existLogs);

            return existLogs.ToList();
        }

        public async Task<QuerySqlResponse> GetSQLResponse(string query, int fetchSize = 0)
        {
            ElasticClient client = GetClient(ConfigService._Config.env.elastic, FORMAT_INDEX_GAME_LOG);
            await UpdateSetting(client, fetchSize);

            QuerySqlResponse querySqlResponse = await client.Sql.QueryAsync(MakeQuerySetting("json", query, fetchSize));

            return querySqlResponse;
        }

        public QuerySqlRequest MakeQuerySetting(string format, string queryStr, int fetchSize)
        {
            QuerySqlRequest query = new QuerySqlRequest();
            query.Format = format;
            query.Query = queryStr;
            if(fetchSize > 0)
            {
                query.FetchSize = fetchSize;
            }

            return query;
        }

        public async Task UpdateSetting(ElasticClient client, int fetchSize)
        {
            if(fetchSize > 0)
            {
                var response = await client.Indices.UpdateSettingsAsync(
                    Indices.All,
                    u => u.IndexSettings(
                        i => i.Setting(
                            UpdatableIndexSettings.MaxResultWindow, fetchSize)
                    )
                );
            }
        }

        public bool CheckElasticOn()
        {
            return false;
        }
    }
}
