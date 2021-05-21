#ifndef INFORM_PACKET1_H
#define INFORM_PACKET1_H

#include "abstract_packet_class.h"

class Inform_packet1: public abstract_packet_class
{
public:
    Inform_packet1();
private:
#pragma pack(push, 1)
    struct data_packet_struct{
        data_packet_struct(){
            memset(this,0x00,sizeof (data_packet_struct));
        }
        char *ptr(void){return (char *)this;}
        int  size(void) {return sizeof (data_packet_struct);}

        uint status:8;
        uint work_id:16;

        float velosity;
        float longituge;
        float lalittude;

        float power;
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

#endif // INFORM_PACKET1_H
