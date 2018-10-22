/*
test for bmp in directory
*/


#include "EasyBMP.h"
#include "EasyBMP.cpp"
#include <cstdlib>
#include <iostream>


using namespace std;

//function to create gasket
void createpattern(BMP & Output, int Xx, int Xy, int Yx, int Yy, int  Zx, int Zy, int Px, int Py, int counter)
{//creates sierpinski gasket from given coordinates, coordinates passed as variables, super hard coded
  if (counter != 0)//holds count for number of iterations
    {
      int chose = rand() % 3;//chose 0-2 logic for each point
      if (chose == 0) //if X is chosen
       {
          //int midpoint;
          int picWidth = (Xx + Px)/2;
          int picHeight = (Xy + Py)/2;
          RGBApixel Temp;
          Temp.Red = 255;
          Temp.Blue = 0;
          Temp.Green = 0;
          Output.SetPixel(picWidth, picHeight, Temp);
          createpattern(Output, Xx, Xy, Yx, Yy, Zx, Zy, picWidth, picHeight, --counter);//recursive call with new midpoint
         
       }
      else if (chose == 1)//if Y is chosen
       {
          //int midpoint;
          int picWidth = (Yx + Px)/2;
          int picHeight = (Yy + Py)/2;
          RGBApixel Temp;
          Temp.Red = 255;
          Temp.Blue = 0;
          Temp.Green = 0;
          Output.SetPixel(picWidth, picHeight, Temp);
          createpattern(Output, Xx, Xy, Yx, Yy, Zx, Zy, picWidth, picHeight, --counter);
         
       }
      else if (chose == 2)//if Z is chosen
       {
          //int midpoint;
          int picWidth = (Zx + Px)/2;
          int picHeight = (Zy + Py)/2;
          RGBApixel Temp;
          Temp.Red = 255;
          Temp.Blue = 0;
          Temp.Green = 0;
          Output.SetPixel(picWidth, picHeight, Temp);
          createpattern(Output, Xx, Xy, Yx, Yy, Zx, Zy, picWidth, picHeight, --counter);
       }
    }
}


//function to create checkerboard
void createBoard(BMP & Output) {
  //creates a 256 X 256 checker board iteratively
  int height = 256; 
  int width = 256;
  Output.SetSize(height, width);
  for (int i = 0; i < width-1; ++i)
    for (int j = 0; j < height-1; ++j) {
      RGBApixel Temp = Output.GetPixel(i,j);
      Temp.Red = 0; Temp.Green = 0; Temp.Blue = 0;
      Output.SetPixel(i,j,Temp);
    }
  for (int i = 0; i < height-1; ++i)
    for (int j = 0; j < width-1; ++j) {
      //boardheight by col, go by col
      RGBApixel Temp1 = Output.GetPixel(i,j);
      if ((i/32 + j/32)%2 == 0)
       {
         Temp1.Red = 255;
         Output.SetPixel(i,j,Temp1);
       }  
    }
}


//functions for tiled image
void scale(BMP & In, BMP & Out) {
  //scale to half the size
  //Rescale (Out, 'p', 50);
  int width = Out.TellWidth()/2;
  int height = Out.TellHeight()/2;
  for (int i = 1; i < width-1; ++i)
    for (int j = 1; j < height-1; ++j) {//rescale, saving red, green, blue values of [k,k], [k,k+1], [k+1,k], and [k+1,k+1]
      //cout << i << 'x' << j << endl;
      int red = (In(2*i, 2*j)->Red + In(2*i+1, 2*j)->Red + In(2*i, 2*j+1)->Red + In(2*i+1, 2*j+1)->Red)/4;
      int green = (In(2*i, 2*j)->Green + In(2*i+1, 2*j)->Green + In(2*i, 2*j+1)->Green + In(2*i+1, 2*j+1)->Green)/4;
      int blue = (In(2*i, 2*j)->Blue + In(2*i+1, 2*j)->Blue + In(2*i, 2*j+1)->Blue + In(2*i+1, 2*j+1)->Blue)/4;
      Out(i,j)->Red = red;
      Out(i,j)->Blue = blue;
      Out(i,j)->Green = green;
    } 
}

void copy(BMP & In, BMP & Out) {
  //copy image to image, In onto Out
  //BMP base = In;
  int baseWid = In.TellWidth();
  int baseHeight = In.TellHeight();
  Out.SetSize(baseWid, baseHeight);
  RangedPixelToPixelCopy(In, 0, baseWid, baseHeight, 0, Out, 0, 0);
}  

void makepattern(BMP & In, BMP & Out) {
  //base case 1x1 pixel, use tellheigth to check 'in', use rangedpixel to copy
  BMP temp;
  int width = In.TellWidth();
  int height = In.TellHeight();
  if (width == 1) {
    RangedPixelToPixelCopy(In, 0, width, height, 0, Out, 0, Out.TellWidth()-1);
    return;
  }
  else {
    temp.SetSize(In.TellWidth()/2, In.TellHeight()/2);
    scale(In, temp);
    RangedPixelToPixelCopy(In, 0, width, height, 0, Out, 0, Out.TellWidth()/2);
    BMP temp1;
    temp1.SetSize(temp.TellWidth(), temp.TellHeight());
    makepattern(temp, temp1);
    RangedPixelToPixelCopy(temp1, 0, temp1.TellWidth(), temp1.TellHeight(), 0, Out, Out.TellHeight()/2, 0);

    RangedPixelToPixelCopy(temp1, 0, temp1.TellWidth()/2, temp1.TellHeight(), 0, Out, 0, 0);
    RangedPixelToPixelCopy(temp1, 0, temp1.TellWidth()/2, temp1.TellHeight(), 0, Out, Out.TellWidth()/4, 0);
    RangedPixelToPixelCopy(temp1, 0, temp1.TellWidth(), temp1.TellHeight()/2, 0, Out, Out.TellWidth()/2, Out.TellHeight()/2);
    RangedPixelToPixelCopy(temp1, 0, temp1.TellWidth(), temp1.TellHeight()/2, 0, Out, Out.TellWidth()/2, Out.TellHeight() * 0.75);

  }
}

 

int main(int argc, char * argv[])
{//the main that does everything

  //create checker board
  BMP board;
  createBoard(board);
  board.WriteToFile("board.bmp");

  //create sierpinski gasket, initialize it as all white
  BMP sierpinski;
  sierpinski.SetSize(256, 256);
  int boardwid = sierpinski.TellWidth();
  int boardHeight = sierpinski.TellHeight();
  for (int i = 0; i < sierpinski.TellWidth()-1; ++i)
    for (int j = 0; j < sierpinski.TellHeight()-1; ++j)
      {
         RGBApixel Temp = sierpinski.GetPixel(i,j);
         Temp.Red = 255;
         Temp.Green = 255;
         Temp.Blue = 255;
         sierpinski.SetPixel(i,j,Temp);
      }
  
  RGBApixel X = sierpinski.GetPixel(128,5);//initialization of first points as red dots
  X.Red = 255;
  X.Blue = 0;
  X.Green = 0;
  sierpinski.SetPixel(128, 5, X);
  RGBApixel Y = sierpinski.GetPixel(5,251);
  Y.Red = 255;
  Y.Blue = 0;
  Y.Green = 0;
  sierpinski.SetPixel(5, 251, Y);
  RGBApixel Z = sierpinski.GetPixel(251, 251);
  Z.Red = 255;
  Z.Blue = 0;
  Z.Green = 0;
  sierpinski.SetPixel(251, 251, Z);
  RGBApixel P = sierpinski.GetPixel(171,34);
  P.Red = 255;
  P.Blue = 0;
  P.Green = 0;
  sierpinski.SetPixel(171, 34, P);
  
  createpattern(sierpinski, 128, 5, 5, 251, 251, 251, 171, 34, 10000);//hard coded points to create gasket
  sierpinski.WriteToFile("sierpinski.bmp");


  //create recursive image from in.bmp
  BMP tile;//main bmp
  tile.ReadFromFile(argv[1]);
  Rescale(tile, 'f', 512);//scale to make sure initial image is power of 2, then use implemented scaling later

  //create second image for rescaling and copying
  BMP image2;
  image2.SetSize(tile.TellWidth(), tile.TellHeight());
  makepattern(tile, image2);

  image2.WriteToFile(argv[2]);
  return 0;
}