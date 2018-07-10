//
// Created by Brendan Berg on 10.07.18.
//

#include "sock/transmissionSocket.hpp"


int TransmissionSocket::receiveData(void* buffer, int length)
{
    return static_cast<int>(recv(m_SockFD, buffer, static_cast<size_t >(length), 0));
}

int TransmissionSocket::sendData(const void* buffer, int length)
{
    return static_cast<int>(send(m_SockFD, buffer, static_cast<size_t>(length), 0));
}
