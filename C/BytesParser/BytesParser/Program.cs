Console.WriteLine("Please enter the lines in the following format: 00000000: f5c4 b159 cc80 e2ef c1c7 c99a 2fb0 0d8c ...Y......../...");
Console.WriteLine("Please write 'end' on the last line to stop");

const string FILE_NAME = "temp.bin";

var bytesAsString = new List<string>();
string? line = string.Empty;

while ((line = Console.ReadLine()) != "end" && line != null)
{
    line
        .Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)
        .Where(s => !string.IsNullOrEmpty(s) && s.Length == 4)
        .ToList()
        .ForEach(part =>
        {
            var first = part.Substring(0, 2);
            var second = part.Substring(2, 2);
            bytesAsString.Add(first);
            bytesAsString.Add(second);
        });
}

var bytes = bytesAsString
    .Select(b => byte.Parse(b, System.Globalization.NumberStyles.HexNumber))
    .ToArray();

File.WriteAllBytes(FILE_NAME, bytes);

