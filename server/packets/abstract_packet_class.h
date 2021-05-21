#ifndef ABSTRACT_PACKET_CLASS_H
#define ABSTRACT_PACKET_CLASS_H
#include <QByteArray>
#include <QDebug>
#include <QVector>

class abstract_packet_class
{
public:
    /**
     * @brief abstract_packet_class
     */
     abstract_packet_class();

    /**
     * @brief ~abstract_packet_class
     */

     virtual ~abstract_packet_class(){}


    /**
     * @brief bytes
     * @return
     */
   virtual QByteArray bytes() = 0;
   virtual bool setBytes(const QByteArray &bytes) = 0;

};

#endif // ABSTRACT_PACKET_CLASS_H
