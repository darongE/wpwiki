#include "work.h"

#include <QNetworkReply>

#include "WPMediaWiki.h"
#include "work_p.h"

// About D-pointer
//https://wiki.qt.io/D-Pointer
namespace mediawiki
{

Work::Work(WorkPrivate &d_work, QObject * const parent)
     : KJob(parent),
       d_ptr(&d_work)
{
    setCapabilities(Work::Killable);
}

Work::~Work()
{
    delete d_ptr;
}

bool Work::doKill()
{
    Q_D(Work);

    if(d->reply != 0)
    {
        d->reply->abort();
    }

    return true;

}

void Work::connectReply()
{
    Q_D(Work);
    connect(d->reply, SIGNAL(uploadProgress(qint64,qint64)),
            this, SLOT(processUploadProgress(qint64,qint64)));
}

//when file is uploading, show bytes size
void Work::processUploadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    setTotalAmount(Work::Bytes, bytesTotal);
    setProcessedAmount(Work::Bytes, bytesReceived);
}


//let's do this..








} //namespace MediaWiki
