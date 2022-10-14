using Nest;
using StatisticsExporter.Model;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StatisticsExporter.Service
{
    public class LogService
    {
        ElasticSearchService elasticSearchService = new();
        ExportService exportService = new();

        /*public async Task RestoreGameLog(string Index)
        {
            bool result = await elasticSearchService.RestoreGameLog(Index);
            if(result)
            {
                Console.WriteLine("{0} 로그 복원에 성공했습니다.", Index);
            }
            else
            {
                Console.WriteLine("{0} 로그 복원에 실패했습니다.", Index);
            }
        }*/
        public void RestoreGameLog(string Index)
        {
            bool result = elasticSearchService.RestoreGameLog(Index);
            if (result)
            {
                Console.WriteLine("{0} 로그 복원에 성공했습니다.", Index);
            }
            else
            {
                Console.WriteLine("{0} 로그 복원에 실패했습니다.", Index);
            }
        }

        public void ExportAU(string logDate, int auCount)
        {
            exportService.ExportAU(logDate, auCount);
        }

        //public async Task<int> GetAU(string yesterdayIndex, string days2Ago)
        public int GetAU(string yesterdayIndex, string days2Ago)
        {
            bool days2AgoExist;
            int result = 0;

            // 무조건 전날은 가져와야한다.
            StringBuilder sb = new StringBuilder("select T,AccUID from \"");
            sb.Append(days2Ago);
            sb.Append("\" WHERE T=101 OR T=102");

            //var days2AgoResult = await elasticSearchService.GetSQLResponse(sb.ToString(), 1000000);
            var days2AgoResult = elasticSearchService.GetSQLResponse(sb.ToString(), 1000000);
            days2AgoExist = days2AgoResult.IsValid;

            // 전날 로그가 있을 경우
            if (days2AgoExist)
            {
                HashSet<int> loginSet = new();
                HashSet<int> logoutSet = new();

                foreach (var row in days2AgoResult.Rows)
                {
                    int T = row[0].As<int>();
                    var AccUID = int.Parse(row[1].As<string>());

                    if (101 == T)
                    {
                        loginSet.Add(AccUID);
                    }
                    else if (102 == T)
                    {
                        logoutSet.Add(AccUID);
                    }
                }

                HashSet<int> remaining = new HashSet<int>(loginSet);
                remaining.ExceptWith(logoutSet);

                sb = new StringBuilder("select T,AccUID from \"");
                sb.Append(yesterdayIndex);
                sb.Append("\" WHERE T=101 OR T=102");

                //var yesterdayResult = await elasticSearchService.GetSQLResponse(sb.ToString(), 1000000);
                var yesterdayResult = elasticSearchService.GetSQLResponse(sb.ToString(), 1000000);

                loginSet = new();
                logoutSet = new();

                foreach (var row in yesterdayResult.Rows)
                {
                    int T = row[0].As<int>();
                    var AccUID = int.Parse(row[1].As<string>());

                    if (101 == T)
                    {
                        loginSet.Add(AccUID);
                    }
                    else if (102 == T)
                    {
                        logoutSet.Add(AccUID);
                    }
                }

                loginSet.UnionWith(remaining);

                result = loginSet.Count();
            }
            else
            {
                sb = new StringBuilder("select count(distinct AccUID) from \"");
                sb.Append(yesterdayIndex);
                sb.Append("\" WHERE T=101");

                //var yesterdayResult = await elasticSearchService.GetSQLResponse(sb.ToString());
                var yesterdayResult = elasticSearchService.GetSQLResponse(sb.ToString());

                foreach (var item in yesterdayResult.Rows)
                {
                    result = Convert.ToInt32(item[0].As<object>());
                }
            }

            return result;
        }
    }
}
