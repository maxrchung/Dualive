using System;
using System.Collections.Generic;
using System.IO;

namespace UpdateFilePaths {
    class Program {
        static void Main(string[] _) {
            var sbFolder = @"C:\Users\Wax Chug da Gwad\Documents\Dualive File Path Updates\Storyboard\";
            var files = Directory.GetFiles(sbFolder, "*.*", SearchOption.AllDirectories);

            var mapFolder = @"C:\Users\Wax Chug da Gwad\Documents\Dualive File Path Updates\";
            var ascii = 97;
            var mappings = new Dictionary<string, string>();

            foreach (var file in files) {
                var sbFilePath = $"\"{file.Replace(mapFolder, "")}\"";
                var shortName = $"{(char)ascii++}";
                Commas(mappings, sbFilePath, shortName);

                // copy file to output
                //var pngName = $"{shortName}.png";
                //File.Copy(file, pngName, true);
            }

            var osbPath = @"C:\Users\Wax Chug da Gwad\Documents\Dualive File Path Updates\Quarks (kradness x Camellia) - Dualive (Haruto).osb";
            // open OSB
            var osb = File.ReadAllText(osbPath);

            // update enums
            Commas(mappings, "TopLeft", "0");
            Commas(mappings, "Centre", "1");
            Commas(mappings, "CentreLeft", "2");
            Commas(mappings, "TopRight", "3");
            Commas(mappings, "BottomCentre", "4");
            Commas(mappings, "TopCentre", "5");
            Commas(mappings, "Custom", "6");
            Commas(mappings, "CentreRight", "7");
            Commas(mappings, "BottomLeft", "8");
            Commas(mappings, "BottomRight", "9");

            Commas(mappings, "Background", "0");
            Commas(mappings, "Fail", "1");
            Commas(mappings, "Pass", "2");
            Commas(mappings, "Foreground", "3");
            Commas(mappings, "Overlay", "4");
            Commas(mappings, "Video", "5");

            mappings.Add("Sprite,", "4,");

            // update file paths
            foreach (var mapping in mappings) {
                osb = osb.Replace(mapping.Key, mapping.Value);
            }

            // write to output
            var outputPath = @"X:\osu!\Songs\Quarks_kradness_x_Camellia_-_Dualive\Quarks (kradness x Camellia) - Dualive (Haruto).osb";
            File.WriteAllText(outputPath, osb);
        }

        private static void Commas(Dictionary<string, string> mappings, string from, string to) => 
            mappings.Add($",{from},", $",{to},");
    }
}
