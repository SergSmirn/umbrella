<<<<<<< HEAD
#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>

#include "main_window.hpp"
#include "setting_window.hpp"

int main(int argc, char ** argv)
{
  QApplication a(argc, argv);

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);


  SettingWindow sw;
  sw.show();

  return a.exec();
}
=======
#include <iostream>
#include "headerlist.hpp"

using namespace std;

int main()
{
   cout << "Hello World!" << endl;
   return 0;
}
>>>>>>> master
