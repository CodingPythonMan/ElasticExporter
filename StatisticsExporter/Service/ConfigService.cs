using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using StatisticsExporter.Config;

namespace StatisticsExporter.Service
{
    public class ConfigService
    {
        public static StatisticsConfig _Config = null!;

        // config 기본 폴더 설정
        private string _basePathDir = string.Empty;
        public string BasePathDir { get { return _basePathDir; } }

        // config 기본 폴더 부터의 폴더명
        // 첫번째는 Release 후 사용
        //public string PATH_CONFIG_FOLDER { get { return BasePathDir + "/"; } }
        public string PATH_CONFIG_FOLDER { get { return BasePathDir + "/../../../../"; } }

        // 로딩할 config 파일들
        const string SERVER_FILE_NAME = "StatisticsConfig";

        public ConfigService()
        {
            InitPath();
            LoadConfig();
        }

        // exe 파일 경로대로 설정
        public void InitPath()
        {
            _basePathDir = Directory.GetCurrentDirectory().ToString();
            Console.WriteLine("Set Base Path {0}", _basePathDir);
        }

        public void LoadConfig()
        {
            var builder = new StringBuilder();
            var checkBuilder = new StringBuilder();

            try
            {
                checkBuilder.AppendFormat("{0}{1}Dev.json", PATH_CONFIG_FOLDER, SERVER_FILE_NAME);

                if (File.Exists(checkBuilder.ToString()))
                {
                    builder.AppendFormat("{0}{1}Dev.json", PATH_CONFIG_FOLDER, SERVER_FILE_NAME);
                }
                else
                {
                    builder.AppendFormat("{0}{1}.json", PATH_CONFIG_FOLDER, SERVER_FILE_NAME);
                }

                Console.WriteLine("{0} load config .. {1}", SERVER_FILE_NAME, builder.ToString());

                string jsonString = File.ReadAllText(builder.ToString());
                _Config = System.Text.Json.JsonSerializer.Deserialize<StatisticsConfig>(jsonString)!;

                builder.Clear();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
                throw;
            }
        }
    }
}
