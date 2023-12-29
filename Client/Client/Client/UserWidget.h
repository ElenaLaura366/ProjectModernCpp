#pragma once
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPixmap>
#include <QString>
#include <optional>
#include "User.h"

class UserWidget : public QWidget {
    Q_OBJECT

public:
    UserWidget(const User& user, QWidget* parent = nullptr);

private:
    User m_user;
};
