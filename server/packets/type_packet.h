#ifndef TYPE_PACKET_H
#define TYPE_PACKET_H
#include "abstract_packet_class.h"

class type_packet: public abstract_packet_class
{
public:
    type_packet();
private:
#pragma pack(push, 1)
    struct data_packet_struct{
        data_packet_struct(){
            memset(this,0x00,sizeof (data_packet_struct));
        }
        char *ptr(void){return (char *)this;}
        int  size(void) {return sizeof (data_packet_struct);}

        uint type:8;
        // добвить сюда все константы

    };

#pragma pack(pop)


    // abstract_packet_class interface
public:
    data_packet_struct *data_packet;

    QByteArray bytes(){
        return QByteArray(data_packet->ptr(),sizeof (data_packet_struct));
    }

    bool setBytes(const QByteArray &bytes){
        if (bytes.size() != sizeof (data_packet_struct))
            return false;
        memcpy(data_packet->ptr(), bytes.data(), sizeof(data_packet_struct));
        return true;
    }
};

#endif // TYPE_PACKET_H
