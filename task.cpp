#include <iostream>
#include <fstream>
#define OFFSET 10
#define JUMPTOWIDTHANDHEIGHT 18
#define JUMPTOSIZEIMAGE 2


using namespace std;

const int fileHeaderSize = 14;
const int informationHeaderSize = 40;

unsigned char fileHeader[fileHeaderSize];
unsigned char informationHeader[informationHeaderSize];

struct RGBColor
{
unsigned char B;
unsigned char G;
unsigned char R;
}kolor;

int x, y;

int main(void)
{

ifstream plik("test.bmp", ios::binary);
ofstream ofs( "negatyw.bmp", ios::binary );

unsigned int width = 0, height = 0, sizeImage = 0;
short offset = 0;
unsigned char c;


plik.seekg(OFFSET, ios::beg);
plik.read((char*)&offset, 2);


plik.seekg(JUMPTOSIZEIMAGE, ios::beg);	
plik.read((char*)&sizeImage, 4);               // wczytywanie rozmiaru pliku

plik.seekg(JUMPTOWIDTHANDHEIGHT, ios::beg);	
plik.read((char*)&width, 4);                   // wczytywanie długości mapyBitowej w pixelach
plik.read((char*)&height, 4);                  // wczytywanie wysokości mapyBitowej w pixelach

plik.seekg(offset, ios::beg);


const int fileSize = fileHeaderSize + informationHeaderSize + width * height;
   
fileHeader[0] = 'B';                         // konieczny zestaw parametrów określający nowy plik
fileHeader[1] = 'M';
fileHeader[2] = fileSize;
fileHeader[3] = fileSize >> 8;
fileHeader[4] = fileSize >> 16;
fileHeader[5] = fileSize >> 24;
fileHeader[6] = 0;
fileHeader[7] = 0;
fileHeader[8] = 0;
fileHeader[9] = 0;
fileHeader[10] = 0;
fileHeader[11] = 0;
fileHeader[12] = 0;
fileHeader[13] = 0;

informationHeader[0] = informationHeaderSize;
informationHeader[1] = 0;
informationHeader[2] = 0;
informationHeader[3] = 0;

informationHeader[4] = width;
informationHeader[5] = width >> 8;
informationHeader[6] = width >> 16;
informationHeader[7] = width >> 24;

informationHeader[8] = height;
informationHeader[9] = height >> 8;
informationHeader[10] = height >> 16;
informationHeader[11] = height >> 24;

informationHeader[12] = 1;
informationHeader[13] = 0;
informationHeader[14] = 24;
informationHeader[15] = 0;

informationHeader[16] = 0;
informationHeader[17] = 0;
informationHeader[18] = 0;
informationHeader[19] = 0;

informationHeader[20] = 0;
informationHeader[21] = 0;
informationHeader[22] = 0;
informationHeader[23] = 0;
informationHeader[24] = 0;
informationHeader[25] = 0;
informationHeader[26] = 0;
informationHeader[27] = 0;
informationHeader[28] = 0;
informationHeader[29] = 0;

informationHeader[30] = 0;
informationHeader[31] = 0;
informationHeader[32] = 0;
informationHeader[33] = 0;
informationHeader[34] = 0;
informationHeader[35] = 0;
informationHeader[36] = 0;
informationHeader[37] = 0;
informationHeader[38] = 0;
informationHeader[39] = 0;

ofs.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);    //  dane nagłówka nowego pliku
ofs.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);   // informacje o nowym pliku

cout << endl;
cout << "metadane pliku: " <<endl ;
cout <<"szerokosc pliku wynosi: "<< width << " px" << endl;
cout <<"wysokosc pliku wynosi " << height << " px" << endl;
cout <<"rozmiar pliku wynosi " << sizeImage << " bajtow" << endl;


for(y = 0; y < height; y++ )      // petle wczytujące dany pixel i zmiana na negatyw
    {
        for(x = 0; x < width; x++ )
        {
          plik.read(( char * ) & kolor, sizeof( RGBColor ) );
          RGBColor kolor2;                     // struktura negatywu
          kolor2.B = 255 - kolor.B;            // zmiana kolorów na negatyw
          kolor2.R = 255 - kolor.R;
          kolor2.G = 255 - kolor.G;
          ofs.write(( char * ) & kolor2, sizeof( RGBColor ) );  // zapis nowej mapy bitowej
        }
    }
    cout << endl;
    cout << "utworzono negatyw obrazka" << endl << endl;


plik.close();
ofs.close();

system("PAUSE");
return 0;
}