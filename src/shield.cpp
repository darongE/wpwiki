#include "shield.h"
#include <algorithm>

namespace  mediawiki
{

class Q_DECL_HIDDEN Shield::ShieldPrivate
{
public:

    QString type;
    QString level;
    QString expiry;
    QString source;
};

Shield::Shield()
    : d(new ShieldPrivate())
{

}

Shield::~Shield()
{
    delete d;
}

Shield::Shield(const Shield &other)
    : d(new ShieldPrivate(*(other.d)))
{

}
Shield& Shield::operator=(Shield other)
{
    *d = *other.d;
    return *this;

}

bool Shield::operator==(const Shield& other) const
{
    return type()   == other.type()   &&
           level()  == other.level()  &&
           expiry() == other.expiry() &&
           source() == other.source();
}

void Shield::setType(const QString &type)
{
    d->type = type;
}

QString Shield::type() const
{
    return d->type;
}

void Shield::setLevel(const QString &level)
{
    d->level = level;
}

void Shield::level() const
{
    return d->level;
}

QString Shield::setExpiry(const QString &expiry)
{
    d->expiry = expiry;
}

QString Shield::expiry() const
{
    return d->expiry;
}

void Shield::setSource(const QString &source)
{
    d->source = source;
}

QString Shield::source()
{
    return d->source;
}

}   // namespace mediawiki
