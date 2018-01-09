using System;
using System.Linq;

namespace RdRand
{
    class Program
    {
        public struct EXIT
        {
            public const int SUCCESS = 0;
            public const int NO_RDRAND = 1;
            public const int HELP = 2;
            public const int INVALID_ARGS = 3;
        }

        public const int BUFFER = 1024 * 4;


        static int Main(string[] args)
        {
#if DEBUG
            args = new string[] { "256" };
#endif

            if (args.Contains("/?"))
            {
                Console.Error.WriteLine(@"RdRand [Amount]
Generates random bytes using the CPU RdRand instruction

Amount    - Number of bytes to generate. Writes to stdout

Won't generate any bytes if no argument is supplied.
Exit codes:
0 = Success
1 = RDRAND is not supported
2 = Help shown
3 = Invalid command line argument");
                return EXIT.HELP;
            }
            else if (args.Length == 0)
            {
                return RdRand_Interop.IsRdRandSupported ? EXIT.SUCCESS : EXIT.NO_RDRAND;
            }
            else
            {
                if (RdRand_Interop.IsRdRandSupported)
                {
                    if (args.Length == 1)
                    {
                        int count = 0;
                        if (int.TryParse(args[0], out count) && count > 0)
                        {
                            var OUT = Console.OpenStandardOutput();
                            for (var i = 0; i < count; i += BUFFER)
                            {
                                OUT.Write(RdRand_Interop.GetRandom(Math.Min(BUFFER, count - i)), 0, Math.Min(BUFFER, count - i));
                            }
                            return EXIT.SUCCESS;
                        }
                    }
                    return EXIT.INVALID_ARGS;
                }
                return EXIT.NO_RDRAND;
            }
        }
    }
}
