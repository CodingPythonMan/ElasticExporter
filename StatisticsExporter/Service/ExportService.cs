using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StatisticsExporter.Service
{
    public class ExportService
    {
        string exportPlace = ConfigService._Config.env.csvStoredFolder + "/Daily";

        public ExportService()
        {
            Directory.CreateDirectory(exportPlace);
        }
        
        public void ExportAU(string logDate, int auCount)
        {
            string place = exportPlace + "/AU.csv";

            StringBuilder sb = new StringBuilder();
            if (!File.Exists(place.ToString()))
            {
                sb.AppendLine("Date,AU");
            }
            sb.AppendLine($"{logDate},{auCount}");

            try
            {
                File.AppendAllText(place, sb.ToString());
            }
            catch(Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}
