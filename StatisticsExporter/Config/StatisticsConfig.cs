using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StatisticsExporter.Config
{
    public class StatisticsConfig
    {
        public Environment env { get; set; } = null!;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// Env
    ////////////////////////////////////////////////////////////////////////////////////////////////

    public class Environment
    {
        public string elastic { get; set; } = null!;
        public string devElastic { get; set; } = null!;
        public string csvStoredFolder { get; set; } = null!;
        public bool dailyServiceValid { get; set; }
        public string dailyServiceStart { get; set; } = null!;
    }
}
