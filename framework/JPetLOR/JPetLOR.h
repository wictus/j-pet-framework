/**
 * @file JPetLOR.h
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2013, Damian Trybek
 * @brief Line of Response Class
 */

#ifndef _JPETLOR_H_
#define _JPETLOR_H_

#include "../JPetHit/JPetHit.h"

#include <cstddef>
#include <utility>

class JPetHit;

/**
 * @brief Data class representing an event with two photon hits recorded in the barrel.
 *
 * An event consists of two hits (JPetHit objects) in two barel slots.
 * Please note that the order of the hits in an event is random.
 */
class JPetLOR: public TNamed 
{  
public:
  JPetLOR();
  JPetLOR(float Time, float QualityOfTime, JPetHit& firstHit, JPetHit& secondHit);
  virtual ~JPetLOR();
  
public:
  /// Get the reconstructed absolute time of the event wrt beginning of the run [ps]
  inline const float getTime() const {return fTime;};
  inline const float getQualityOfTime() const {return fQualityOfTime;};
  /// Set the reconstructed absolute time of the event wrt beginning of the run [ps]
  inline void setTime(float time) {fTime = time;};
  inline void setQualityOfTime(float qualityOfTime) {fQualityOfTime = qualityOfTime;};
  inline const JPetHit& getFirstHit() const {return fFirstHit;};
  inline const JPetHit& getSecondHit() const {return fSecondHit;};
  /**
   * @brief Access the hits of the event as elements if an array
   *
   * @param i should be either 0 or 1 as the event can have 0-2 hits
   */
  const JPetHit & operator[](int i) const;
  //inline const JPetHits& GetHits() const {return *fHits;};
  // inline void SetHits(JPetHits* hits) {fHits = hits;};
  // inline void SetHits(JPetHits& hits) {fHits = &hits;};
  /**
   * @brief Set both hits of this event at once.
   */
  inline void setHits(JPetHit & firstHit, JPetHit & secondHit) {
    fFirstHit = firstHit;
    fSecondHit = secondHit;
    fNhits = 2;
  }
  /**
   * @brief Set the first hit of this event.
   *
   * Using this method the user is responsible for controlling which hit is first and second and ensuring that both hits of the events are set. 
   */
  inline void setFirstHit(JPetHit & firstHit) {fFirstHit = firstHit; }
  /**
   * @brief Set the second hit of this event.
   *
   * Using this method the user is responsible for controlling which hit is first and second and ensuring that both hits of the events are set.
   */
  inline void setSecondHit(JPetHit & secondHit) {fSecondHit = secondHit; };
  /**
   * @brief Add a JPetHit object to this event
   *
   * Use this method and the [] operator rather than Set(Get)FirstHit and Set(Get)SecondHit if you don't want to manually control which hit is first and which second. Just call AddHit twice to set the hits in the event. They can be later accessed as event[0] and event[1].
   *
   * @return number of hits set in this event after adding the provided hit (i.e. 1 or 2), or 0 if the event already had two set hits (and the new hit was not added).
   */
  int addHit(JPetHit & hit);
  /// Set the reconstructed time difference between the two hits of the event [ps]
  inline void setTimeDiff(float td) {fTimeDiff = td;}
  inline void setQualityOfTimeDiff(float qtd) {fQualityOfTime = qtd;}
  inline float getTimeDiff() const { return fTimeDiff; }

  ClassDef(JPetLOR,1);

  private:
  
  float fTime; ///< reconstructed absolute time of the event wrt to beginning of the run [ps]
  float fQualityOfTime;
  
  float fTimeDiff; ///< reconstructed time difference between the two hits of the event [ps]
  float fQualityOfTimeDiff;

  JPetHit fFirstHit;
  JPetHit fSecondHit;
  unsigned short int fNhits;

};

#endif