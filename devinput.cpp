#include "devinput.h"
#include <QDebug>
devinput::devinput(QObject *parent) : QObject(parent)
{

}

devinput::~devinput()
{

}

void devinput::process()
{
    // allocate resources using new here
    struct input_event ev;
    int fd, rd;

    //Open Device
    if ((fd = open ("/dev/input/event0", O_RDONLY|O_NONBLOCK)) == -1)
    {
        printf ("not a vaild device.\n");

        emit finished();
        return;
    }

    bool bOnTablet = false;
    memset((void*)&ev, 0, sizeof(ev));
    while (1)
    {


        rd = read (fd, (void*)&ev, sizeof(ev));

        if (ev.code == evdev_pen::evcode_stylus_present)
        {
//            qDebug() << (ev.value == 1 ? "Stylus Present" : "Stylus Left");
            emit stylusPresence(bool(ev.value));
        }
        else if (ev.code == evdev_pen::evcode_stylus_pressure)
        {
            if(ev.value > 600 )
            {
                if(!bOnTablet)
                {
//                    qDebug() << "Pen is on the tablet";

                    emit stylusOnTablet(true);
                }
                bOnTablet = true;
            }
            else if (ev.value < 400 && bOnTablet)
            {
                bOnTablet = false;
//                qDebug() << "Pen left the tablet's surface";
                emit stylusOnTablet(false);
            }

        }

//        if(rd>0 && ev.value==0 && ev.type==1)
//        {
//            printf("type: %d, code: %d, value: %d, rd: %d\n", ev.type, ev.code, ev.value, rd);
//        }
    }

    emit finished();
}
