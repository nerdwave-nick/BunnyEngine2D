#pragma once
#include "typedefs.h"

namespace Bunny {
  class Timestep {
   public:
    Timestep(bu_f32 time = 0.0f) :
        m_Time(time) {}
    operator bu_f32() const {
      return m_Time;
    }
    bu_f32 GetSeconds() const {
      return m_Time;
    }
    bu_f32 GetSMilliseconds() const {
      return m_Time * 1000.0f;
    }

   private:
    friend class Application;
    friend class Time;
    bu_f32 m_Time;
    static Timestep s_DeltaTime;
  };
  class Time {
   public:
    static Timestep DeltaTime() {
      return Timestep::s_DeltaTime;
    }
  };
  // float operator*(bu_f32 f, Timestep ts) { return f * ts.GetSeconds(); }
  // float operator*(Timestep ts, float f) { return f * ts.GetSeconds(); }
}  // namespace Bunny