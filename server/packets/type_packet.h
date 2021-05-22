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
            memset(this,0x00,sizeof (uint8_t));
        }
        char *ptr(void){return (char *)this;}
        int  size(void) {return sizeof (uint8_t);}

        uint type:8;
        // добвить сюда все константы

    };

#pragma pack(pop)


    // abstract_packet_class interface
public:
    data_packet_struct *data_packet;

    QByteArray bytes(){
        return QByteArray(data_packet->ptr(),sizeof (uint8_t));
    }

    bool setBytes(const QByteArray &bytes){
        if (bytes.size() != sizeof (uint8_t))
            return false;
        memcpy(data_packet->ptr(), bytes.data(), sizeof(uint8_t));
        return true;
    }
};

#endif // TYPE_PACKET_H
