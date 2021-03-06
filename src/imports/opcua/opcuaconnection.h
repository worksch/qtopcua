/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt OPC UA module.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#pragma once

#include <QObject>
#include <QOpcUaClient>

QT_BEGIN_NAMESPACE

class OpcUaConnection : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(OpcUaConnection)
    Q_PROPERTY(QStringList availableBackends READ availableBackends NOTIFY availableBackendsChanged)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(QString backend READ backend WRITE setBackend NOTIFY backendChanged)
    Q_PROPERTY(bool defaultConnection READ defaultConnection WRITE setDefaultConnection NOTIFY defaultConnectionChanged)
    Q_PROPERTY(QStringList namespaces READ namespaces NOTIFY namespacesChanged)

public:
    OpcUaConnection(QObject *parent = nullptr);
    ~OpcUaConnection();
    QStringList availableBackends() const;
    bool connected() const;
    void setBackend(const QString &name);
    QString backend() const;
    static OpcUaConnection *defaultConnection();
    bool isDefaultConnection() const;
    QStringList namespaces() const;

public slots:
    void connectToEndpoint(const QUrl &url);
    void disconnectFromEndpoint();
    void setDefaultConnection(bool defaultConnection = true);

signals:
    void availableBackendsChanged();
    void connectedChanged();
    void backendChanged();
    void defaultConnectionChanged();
    void namespacesChanged();

private slots:
    void clientStateHandler(QOpcUaClient::ClientState state);

private:
    QOpcUaClient *m_client = nullptr;
    bool m_connected = false;
    static OpcUaConnection* m_defaultConnection;

friend class OpcUaNode;
friend class OpcUaValueNode;
friend class OpcUaMethodNode;
};

QT_END_NAMESPACE
