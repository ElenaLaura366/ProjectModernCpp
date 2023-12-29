#include "UserWidget.h"

UserWidget::UserWidget(const User& user, QWidget* parent) : 
    QWidget{ parent }, 
    m_user{ user }
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    QLabel* imageLabel = new QLabel(this);
    QLabel* nameLabel = new QLabel(m_user.getUsername(), this);

    QPixmap userImage(":avatar.png");
    imageLabel->setPixmap(userImage.scaled(50, 50, Qt::KeepAspectRatio));

    layout->addWidget(imageLabel);
    layout->addWidget(nameLabel);
}
