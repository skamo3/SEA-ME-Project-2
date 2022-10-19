#ifndef CANRECEIVER_H
#define CANRECEIVER_H

#include <QObject>
#include <linux/can.h>
#include "datamanager_interface.h"

# define COLOR_RED		"\x1b[31m"
# define COLOR_GREEN	"\x1b[32m"
# define COLOR_YELLOW	"\x1b[33m"
# define COLOR_BLUE		"\x1b[34m"
# define COLOR_MAGENTA	"\x1b[35m"
# define COLOR_CYAN		"\x1b[36m"
# define COLOR_WHITE	"\x1b[37m"
# define COLOR_BRED		"\x1b[91m"
# define COLOR_BGREEN	"\x1b[92m"
# define COLOR_BYELLOW	"\x1b[93m"
# define COLOR_BBLUE	"\x1b[94m"
# define COLOR_BMAGENTA	"\x1b[95m"
# define COLOR_BCYAN	"\x1b[96m"
# define COLOR_RESET	"\x1b[0m"

# define CAN_FRAME_MAX_LEN 8

class CanReceiver : public QObject
{
    Q_OBJECT

public:
    explicit CanReceiver(QObject *parent = nullptr);
    CanReceiver(CanReceiver const &origin);
    CanReceiver &operator=(CanReceiver const &origin);
    ~CanReceiver();

    void initSocket(const QString &ifname);
    void initDBusServer(const QString &serverName, const QString &objName);

    void startCommunicate();

private:
    int socketFD;
    struct can_frame canFrame;
    local::DataManager *dataManager;
    std::shared_ptr<class QTimer> canTimer;
    std::shared_ptr<class QTimer> dbusTimer;

signals:

public slots:
    int readData();
    void sendCanDataToServer();

};

#endif // CANRECEIVER_H
