#include "DialogProvider.h"

DialogProvider* DialogProvider::m_instance = nullptr;

DialogProvider::DialogProvider(QObject *parent) : QObject(parent) {}

void DialogProvider::requestDialog(int level, const QString &body)
{
    emit dialogRequested(level, body);
}
