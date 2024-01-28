class Program
{
    static void Main(string[] args)
    {
        string filename = args.Length > 0 ? args[0] : null;

        using var game = new mymonogame.Game1(filename);
        game.Run();
    }
}
