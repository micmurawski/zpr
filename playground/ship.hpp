class Ship{
public:
	virtual int getHP() const {return hp_};
	virtual int getDamage() const {return damage};
	virtual void modifyHP(int hp)=0;
	virtual int getMovePoints() const {return move_points_};
private:
	unsigned int max_hp_;
	unsigned int move_points_;
	unsigned int hp_;
	unsigned int id_;
	};

class BasicShip : public Ship{
public:
	virtual void modifyHP(int hp) {hp_ = (hp_-hp>0) ? (hp_-hp)%max_hp_ : 0;}
	BasicShip(int id): max_hp_(90), move_points(1), hp_(90), id_(id) {}
private:
	unsigned int max_hp_;
	unsigned int move_points_;
	unsigned int hp_;
	unsigned int id_;
	};
