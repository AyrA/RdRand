namespace RdRand
{
    class Program
    {
        public struct EXIT
        {
            public const int SUCCESS = 0;
            public const int NO_RDRAND = 1;
        }

        static int Main(string[] args)
        {
            if (RdRand_Interop.IsRdRandSupported)
            {
                byte[] data = RdRand_Interop.GetRandom(1024);
                return EXIT.SUCCESS;
            }
            return EXIT.NO_RDRAND;
        }
    }
}
