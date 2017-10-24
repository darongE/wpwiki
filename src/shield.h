#ifndef Shield_H
#define Shield_H

#include <QString>

#include "mediawiki_export.h"

namespace  mediawiki
{
/**
 * @brief The Shield class
 *  role : protected parameter in page
 */


  class MEDIAWIKI_EXPORT Shield
  {


  public:

      Shield();

      /**
       * @brief Make Protect part from others
       * @param other: other shield
       */
      Shield(const Shield& other);
      ~Shield();

      /**
       * @brief Returns true if this instance and other are equal, else false
       * @param other : instance to compare
       * @return true if there are equal
       *
       */
      Shield& operator=(Shield other);

      /**
       * @brief Retunrn true if this instance and other are equal, else false
       * @param other instance to compare
       * @return true if equal , else false
       */
      bool operator==(const Shield& other) const;

      /**
       * @brief Set the shield type
       * @param type
       */
      void setType(const QString& type);

      /**
       * @brief Get the shield type
       * @return shield type
       */
      QString type() const;

      /**
       * @brief setLevel
       * @param level
       */

      void setLevel(const QString& level);

      /**
       * @brief page shield level
       * @return page shild level
       */
      QString level() const;

      /**
       * @brief Set the expiry date
       * @param expiry date
       */
      void setExpiry(const QString& expiry);

      /**
       * @brief get the expiry date
       * @return expiry date
       */
      QString expiry() const;

      /**
       * @brief get the source
       * @param the source
       */
      void setSource(const QString& source);

      /**
       * @brief Get the source
       * @return the source
       */
      QString source() const;

  private:
      class ShieldPrivate;
      ShieldPrivate* const d;

  };
}


#endif // Shield_H
