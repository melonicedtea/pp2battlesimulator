#pragma once

namespace Tmpl8
{
//forward declarations
class Tank;
class Rocket;
class Smoke;
class ParticleBeam;

class Game
{
  public:
    void SetTarget(Surface* surface) { screen = surface; }
    void Init();
    void Shutdown();
    void Update(float deltaTime);
    void Draw();
    void Tick(float deltaTime);
    void insertion_sort_tanks_health(const std::vector<Tank>& original, std::vector<const Tank*>& sorted_tanks, UINT16 begin, UINT16 end);
    void MeasurePerformance();

    Tank& FindClosestEnemy(Tank& current_tank);

    void MouseUp(int button)
    { /* implement if you want to detect mouse button presses */
    }

    void MouseDown(int button)
    { /* implement if you want to detect mouse button presses */
    }

    void MouseMove(int x, int y)
    { /* implement if you want to detect mouse movement */
    }

    void KeyUp(int key)
    { /* implement if you want to handle keys */
    }

    void KeyDown(int key)
    { /* implement if you want to handle keys */
    }

  private:
    Surface* screen;

    vector<Tank> tanks;
    vector<Rocket> rockets;
    vector<Smoke> smokes;
    vector<Explosion> explosions;
    vector<ParticleBeam> particle_beams;

    Font* frame_count_font;
    long long frame_count = 0;

    bool lock_update = false;

	vector<Tank*> tank_ptrs;
};

}; // namespace Tmpl8