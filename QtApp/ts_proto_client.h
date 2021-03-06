/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtBluetooth module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef TS_PROTO_CLIENT_H
#define TS_PROTO_CLIENT_H

#include <qbluetoothserviceinfo.h>

#include <QtCore/QObject>
#include <QTimer>

#include "ts_proto.h"

#include "average_buffer.h"


QT_FORWARD_DECLARE_CLASS(QBluetoothSocket)

QT_USE_NAMESPACE


class tsProtoClient : public QObject
{
    Q_OBJECT
private:
    QTimer *m_syncTimer = 0;

    std::unique_ptr<AverageBuffer<uint32_t>> m_maxdT;


    bool m_timeIsSynchronized = false;

    tsTime_t m_lastMsgTS;
    uint32_t m_latency = 0;

    void initTimer();
    void freeTimer();

    QString m_name;
    QString m_addr;

public:
    explicit tsProtoClient(QObject *parent = 0);
    ~tsProtoClient();

    void startClient(const QBluetoothServiceInfo &remoteService);
    void stopClient();

    QString getName() const;
    QString getAddr() const;

public slots:
    void sendMessage(const QString &message);

signals:
    void messageReceived(const QString &sender, const QString &message);
    void connected(const QString &name, const QString &addr);
    void disconnected(const QString &addr);
    void latencyChanged(const QString &addr, const uint32_t latency);

private slots:
    void syncTime();
    void m_readyRead();
    void m_connected();
    void m_disconnected();


private:
    QBluetoothSocket *socket;
};


#endif // CHATCLIENT_H
