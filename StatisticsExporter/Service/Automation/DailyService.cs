using Nest;
using StatisticsExporter.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StatisticsExporter.Service.Automation
{
    public class DailyService
    {
        LogService logService = new();

        DateTime today = DateTime.Today;

        string todayStr { get; set; }
        string yesterdayIndex { get; set; }

        public DailyService()
        {
            todayStr = today.ToString("yyyy.MM.dd");
            yesterdayIndex = ConvertDateToIndex(today.AddDays(-1));
        }

        public async Task Start(bool permission)
        {
            if(permission)
            {
                Console.WriteLine("{0} : Daily Service 활성화 상태입니다.", todayStr);
                //int[] dailyResult = await GetDailyResult();
                int[] dailyResult = GetDailyResult();
                ExportDaily(dailyResult);
            }
            else
            {
                Console.WriteLine("{0} : Daily Service 비활성화 상태입니다.", todayStr);
            }
        }

        //public async int[] GetDailyResult()
        public int[] GetDailyResult()
        {
            int[] dailyResult = new int[16];

            //await logService.RestoreGameLog(yesterdayIndex);
            logService.RestoreGameLog(yesterdayIndex);
            //dailyResult.AU = await logService.GetAU(yesterdayIndex, ConvertDateToIndex(today.AddDays(-2)));
            int j = 0;
            for (int i=-14; i<-1; i++)
            {
                //dailyResult[j] = await logService.GetAU(ConvertDateToIndex(today.AddDays(i)), ConvertDateToIndex(today.AddDays(i-1)));
                dailyResult[j] = logService.GetAU(ConvertDateToIndex(today.AddDays(i)), ConvertDateToIndex(today.AddDays(i-1)));
                j++;
            }

            return dailyResult;
        }

        public void ExportDaily(int[] dailyResult)
        {
            int j = 0;
            for (int i = -14; i < -1; i++)
            {
                logService.ExportAU(today.AddDays(i).ToString("yyyy.MM.dd"), dailyResult[j]);
                j++;
            }
        }

        public string ConvertDateToIndex(DateTime dt)
        {
            string result = "gamelog_" + dt.ToString("yyyy.MM.dd");

            return result;
        }
    }
}
