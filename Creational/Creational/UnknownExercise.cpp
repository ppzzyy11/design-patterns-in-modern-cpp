#include <vector>
#include <gtest/gtest.h>
using namespace std;

struct Game;
struct StatQuery;

enum class Statistic
{
  Attack,
  Defense
};

struct StatQuery
{
  Statistic statistic;
  int result = 0;
};

class Creature
{
protected:
  Game& game;
  int baseAttack, baseDefense;

public:
  Creature(Game& game, const int baseAttack, const int baseDefense)
    : game{game},
      baseAttack{baseAttack},
      baseDefense{baseDefense}
  {
  }

  virtual int attack() const { return baseAttack; }
  virtual int defense() const { return baseDefense; }

  virtual void query(const void* source, StatQuery& query) const = 0;
};

struct Game
{
  vector<Creature*> creatures;
};

class Goblin : public Creature
{
  int doQuery(const Statistic s) const
  {
    StatQuery q{s};
    for (const auto& c : game.creatures)
    {
      c->query(this, q);
    }
    return q.result;
  }

public:

  Goblin(Game& game, const int baseAttack, const int baseDefense)
    : Creature{game, baseAttack, baseDefense}
  {
  }

  Goblin(Game& game)
    : Creature{game, 1, 1}
  {
  }

  int attack() const override
  {
    return doQuery(Statistic::Attack);
  }

  int defense() const override
  {
    return doQuery(Statistic::Defense);
  }

  void query(const void* source, StatQuery& query) const override
  {
    if (source == this)
    {
      switch (query.statistic)
      {
      case Statistic::Attack:
        query.result += baseAttack;
        break;
      case Statistic::Defense:
        query.result += baseDefense;
        break;
      }
    }
    else
    {
      if (query.statistic == Statistic::Defense)
      {
        query.result++;
      }
    }
  }
};

class GoblinKing : public Goblin
{
public:
  explicit GoblinKing(Game& game)
    : Goblin{game, 3, 3}
  {
  }

  void query(const void* source, StatQuery& query) const override
  {
    if (source != this && query.statistic == Statistic::Attack)
    {
      query.result++;
    }
    else
    {
      Goblin::query(source, query);
    }
  }
};

#include "gtest/gtest.h"

//#include "helpers/iohelper.h"

//#include "exercise.cpp"


namespace
{
  class Evaluate : public testing::Test
  {
  public:
    Game game;
  protected:
    Evaluate()
    {
      // You can do set-up work for each test here.
    }

    virtual ~Evaluate()
    {
      // You can do clean-up work that doesn't throw exceptions here.
    }

    // Objects declared here can be used by all tests in the test case for Foo.
  };

  TEST_F(Evaluate, SingleGoblinTest)
  {
    Goblin goblin{game};
    game.creatures.push_back(&goblin);
    ASSERT_EQ(1, goblin.attack()) << "Single goblin's attack must be = 1";
    ASSERT_EQ(1, goblin.defense()) << "Single goblin's defense must be = 1";
  }

  TEST_F(Evaluate, TwoGoblinTest)
  {
    Goblin goblin{ game }, goblin2{ game };
    game.creatures.push_back(&goblin);
    game.creatures.push_back(&goblin2);

    ASSERT_EQ(1, goblin.attack()) << "2 goblins in play, expecting Goblin's attack to be = 1";
    ASSERT_EQ(2, goblin.defense()) << "2 goblins in play, expecting Goblin's defense to be = 2";
    
    ASSERT_EQ(1, goblin2.attack()) << "2 goblins in play, expecting Goblin's attack to be = 1";
    ASSERT_EQ(2, goblin2.defense()) << "2 goblins in play, expecting Goblin's defense to be = 2";
  }

  TEST_F(Evaluate, GoblinCohortTest)
  {
    Goblin goblin{ game }, goblin2{ game };
    GoblinKing king{ game };
    game.creatures.push_back(&goblin);
    game.creatures.push_back(&goblin2);
    game.creatures.push_back(&king);

    ASSERT_EQ(2, goblin.attack());
    ASSERT_EQ(3, goblin.defense());

    ASSERT_EQ(2, goblin2.attack());
    ASSERT_EQ(3, goblin2.defense());

    ASSERT_EQ(3, king.attack());
    ASSERT_EQ(5, king.defense());
  }
} // namespace


int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
