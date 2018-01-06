#ifndef PLANETDETAILS_HPP
#define PLANETDETAILS_HPP

#include <QFrame>
#include <QLabel>
#include <QLineEdit>

class PlanetDetails : public QFrame {
public:
    PlanetDetails();
private:
    QLabel* labels_[4];
    QLineEdit* properties_[4];
};

#endif // PLANETDETAILS_HPP
