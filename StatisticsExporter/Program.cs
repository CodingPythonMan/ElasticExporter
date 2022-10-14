using StatisticsExporter.Service;
using StatisticsExporter.Service.Automation;

ConfigService configService = new();
DailyService dailyService = new();

dailyService.Start(ConfigService._Config.env.dailyServiceValid).Wait();

foreach(var item in args)
{
    Console.WriteLine(args);
}