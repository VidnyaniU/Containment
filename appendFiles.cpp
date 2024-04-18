#include <bits/stdc++.h>
using namespace std;
int main()
{
    // Define the names of the four files to append
    string filename0 = "result_0.txt";
    string filename1 = "result_1.txt";
    string filename2 = "result_2.txt";
    string filename3 = "result_3.txt";

    // Define the name of the output file
    string outputFilename = "final_output_2by2.txt";

    // Open the output file in append mode
    ofstream outputFile(outputFilename, ios::app);

    if (outputFile.is_open())
    {
        // Loop through each file to append its contents
        for (const string &filename : {filename0, filename1, filename2, filename3})
        {
            // Open the current file in read mode
            ifstream currentFile(filename);

            if (currentFile.is_open())
            {
                // Read the entire content of the file and append it to the output file
                string line;
                while (getline(currentFile, line))
                {
                    outputFile << line << endl;
                }

                // Close the current file
                currentFile.close();
            }
            else
            {
                cerr << "Error opening file: " << filename << endl;
            }
        }

        cout << "Files appended successfully to " << outputFilename << endl;
    }
    else
    {
        cerr << "Error opening output file: " << outputFilename << endl;
    }

    // Close the output file
    outputFile.close();

    return 0;
}
