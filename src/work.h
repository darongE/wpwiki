#ifndef MEDIAWIKIWORK_H
#define MEDIAWIKIWORK_H

//KDE includes

#include <KCoreAddons/KJob>

//Local includes
#include "mediawiki_export.h"

namespace  mediawiki {

class MediaWiki;
class WorkPrivate;

/**
 * @brief The base class for all MediaWiki work
 */
 class MEDIAWIKI_EXPORT Work : public KJob
 {
     Q_OBJECT
     Q_DECLARE_PRIVATE(Work)

 public:

     /**
      * @brief Indicates all possible error case found during the processing of the job
      */

     enum
     {
        NetworkError            = KJob::UserDefinedError + 1,
        JsonError,
        XmlError,
        UserRequestDefinedError = KJob::UserDefinedError + 100,
        MissingMandatoryParameter
     };

 public:
     /**
      * @brief Destructs the work
      */
     virtual ~Work();

     /**
      * @brief Aborts work
      */

     bool doKill() Q_DECL_OVERRIDE;

 protected:

     /**
      * @brief Constructs Work as private class
      * @param d_work : private class
      * @param parent : Object parent
      *
      */

     Work(WorkPrivate& d_work, QObject* const parent = 0);

     /**
      * @brief Connects signals of the reply object (in the private
      *        object) to slots of this base class.
      */

      void connectReply();


     /**
      * @brief private d pointer
      *
      */

      WorkPrivate* const d_ptr;

    private Q_SLOTS:

      void processUploadProgress(qint64 bytesReceived,qint64 bytesTotal);

 };

}  //namespace mediawiki



#endif // MEDIAWIKIWORK_H
