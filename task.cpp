#include <iostream>
#include <fstream>
#define OFFSET 10
#define BMP_RES 18

using namespace std;

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

unsigned int width = 0, height = 0;
short offset = 0;
unsigned char c;
plik.seekg(OFFSET, ios::beg);
plik.read((char*)&offset, 2);
plik.seekg(BMP_RES, ios::beg);	
plik.read((char*)&width, 4);
plik.read((char*)&height, 4);
plik.seekg(offset, ios::beg);

ofs.write(( char * ) &width, 4 );
ofs.write(( char * ) &height, 4 );


cout << width << endl;
cout << height << endl;

for(y = 0; y < height; y++ )
    {
        for(x = 0; x < width; x++ )
        {
            plik.read(( char * ) & kolor, sizeof( RGBColor ) );
          //  cout <<( int ) kolor.R << " " <<( int ) kolor.G << " " <<( int ) kolor.B << ", ";
            ofs.write(( char * ) & kolor, sizeof( RGBColor ) );
        }
       
        cout << endl;
    }




// int x, y;
// for(y = 0; y < height; y++)	
// {
// 	for(x = 0; x < width; x++)
// 	{
// 		plik.read((char*)&kolor, sizeof(RGBColor));
// 		if(kolor.R == 0 && kolor.G == 0 && kolor.B == 0) cout << "1";
// 		else if(kolor.R == 255 && kolor.G == 0 && kolor.B == 0) cout << "S";
// 		else if(kolor.R == 0 && kolor.G == 0 && kolor.B == 255) cout << "T";
// 		else cout << " ";
// 	}
// 	plik.read((char*)&kolor, sizeof(RGBColor));
// 	cout << endl;
// }
plik.close();
ofs.close();

system("PAUSE");
return 0;
}