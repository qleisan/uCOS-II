using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace mymonogame;

using System;
using System.IO;

public class FileReader
{
    public static string ReadLastLine(string filePath)
    {
        string lastLine = null;

        try
        {
            // Open the file with FileShare.Read to allow other processes to read the file simultaneously
            using (FileStream fileStream = new FileStream(filePath, FileMode.Open, FileAccess.Read, FileShare.Read))
            {
                using (StreamReader reader = new StreamReader(fileStream))
                {
                    string line;
                    while ((line = reader.ReadLine()) != null)
                    {
                        lastLine = line;
                    }
                }
            }
        }
        catch (IOException)
        {
            // File is being used by another process
            return "unavailable";
        }

        return lastLine;
    }
}



public class Game1 : Game
{
    private GraphicsDeviceManager _graphics;
    private SpriteBatch _spriteBatch;

    public Game1()
    {
        _graphics = new GraphicsDeviceManager(this);
        Content.RootDirectory = "Content";
        IsMouseVisible = true;

        _graphics.PreferredBackBufferWidth = 250;
        _graphics.PreferredBackBufferHeight = 400;
    }

    protected override void Initialize()
    {
        // TODO: Add your initialization logic here

        base.Initialize();
    }

    protected override void LoadContent()
    {
        _spriteBatch = new SpriteBatch(GraphicsDevice);

        // TODO: use this.Content to load your game content here
    }

    private bool greenCircleOn = false;
    private bool yellowCircleOn = true;
    private bool redCircleOn = true;


    protected override void Update(GameTime gameTime)
    {
        if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
            Exit();

        Console.WriteLine(gameTime); // Print gameTime to console


        // Get the current working directory
        string currentDirectory = Directory.GetCurrentDirectory();
        // Print the current working directory
        Console.WriteLine($"Current Working Directory: {currentDirectory}");

        // string filePath = "..\\..\\..\\mylog.txt";

        // WSL instance name (replace 'YourWSLInstance' with the actual instance name)
        string wslInstance = "Ubuntu";
        // Path to the file within the WSL instance
        string wslFilePath = "/home/qleisan/TrafficLights/EvalBoards/linux/linux32/GNU/OS/TrafficLight1.log";
        // Construct the Windows path to the WSL file
        string filePath = $@"\\wsl$\{wslInstance}{wslFilePath.Replace('/', '\\')}";

        // filePath = "/home/qleisan/uCOS-II/EvalBoards/linux/linux32/GNU/OS/Task1.log";
        filePath = "../EvalBoards/linux/linux32/GNU/OS/Task1.log";

        // Access the file using the Windows path
        try
        {
            string content = File.ReadAllText(filePath);
            // Console.WriteLine(content);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error accessing the file: {ex.Message}");
        }


        string lastLine = FileReader.ReadLastLine(filePath);

        if (lastLine != null)
        {
            Console.WriteLine("Last line of the file: " + lastLine);
        }
        else
        {
            Console.WriteLine("File is empty.");
        }

        if (int.TryParse(lastLine, out int lastLineInt))
        {
            Console.WriteLine("Last line of the file (as integer): " + lastLineInt);

            if ((lastLineInt & 1) == 1) 
            {
                greenCircleOn = true;

            }
            else
            {
                greenCircleOn = false;
            }

            if ((lastLineInt & 2) == 2)
            {
                yellowCircleOn = true;
            }
            else
            {
                yellowCircleOn = false;
            }

            if ((lastLineInt & 4) == 4)
            {
                redCircleOn = true;
            }
            else
            {
                redCircleOn = false;
            }
        }

        // TODO: Add your update logic here

        base.Update(gameTime);
    }



    protected override void Draw(GameTime gameTime)
    {
        GraphicsDevice.Clear(Color.Black);

        _spriteBatch.Begin();

        int radius = 50;
        int offsetY = 100;
        int centerX = GraphicsDevice.Viewport.Width / 2;
        int centerY = GraphicsDevice.Viewport.Height / 2;

        // Draw the green circle
        Color greenColor = greenCircleOn ? Color.Green : Color.Green * 0.3f; // Set transparency to 0% or 30%
        Texture2D greenCircleTexture = CreateCircleTexture(radius * 2, greenColor);
        _spriteBatch.Draw(greenCircleTexture, new Vector2(centerX - radius, offsetY + centerY - radius), Color.White);

        // Draw the yellow circle
        Color yellowColor = yellowCircleOn ? Color.Yellow : Color.Yellow * 0.3f; // Set transparency to 0% or 30%

        Texture2D yellowCircleTexture = CreateCircleTexture(radius * 2, yellowColor);
        _spriteBatch.Draw(yellowCircleTexture, new Vector2(centerX - radius, offsetY + centerY - radius * 3), Color.White);

        // Draw the red circle
        Color redColor = redCircleOn ? Color.Red : Color.Red * 0.3f; // Set transparency to 0% or 30%
        Texture2D redCircleTexture = CreateCircleTexture(radius * 2, redColor);
        _spriteBatch.Draw(redCircleTexture, new Vector2(centerX - radius, offsetY + centerY - radius * 5), Color.White);

        _spriteBatch.End();

        base.Draw(gameTime);
    }

    private Texture2D CreateCircleTexture(int diameter, Color color)
    {
        int radius = diameter / 2;
        int centerX = radius;
        int centerY = radius;

        Color[] data = new Color[diameter * diameter];

        for (int y = 0; y < diameter; y++)
        {
            for (int x = 0; x < diameter; x++)
            {
                int index = x + y * diameter;
                Vector2 position = new Vector2(x - centerX, y - centerY);

                if (position.Length() <= radius)
                {
                    data[index] = color;
                }
                else
                {
                    data[index] = Color.Transparent;
                }
            }
        }

        Texture2D texture = new Texture2D(GraphicsDevice, diameter, diameter);
        texture.SetData(data);

        return texture;
    }
}
