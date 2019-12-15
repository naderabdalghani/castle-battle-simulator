#pragma once
#include "../qeueu.h"
#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include <string>
// Enemy is the base class of each type of enemy
// Enemy is an abstract class.
class Enemy
{

protected:
	int speed;
	int ID;         //Each enemy has a unique ID (sequence number)
	color Clr;	    //Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	string clr;     //Image ID Nader
	REGION Region;  //Region of this enemy
	int Distance;	//Horizontal distance between enemy & the tower of its region
	                //Always positive (ranges from 2 to 60)
	double Health;	//Enemy health

	///////////// ADDED /////////////
	int ArrivalTime;
	int Type;        // 0: paver, 1: fighter, 2: shielded
	int FirePower;
	int ReloadPeriod;
	int state;     // 0: killed , 1: active -1: inactive ,
	int FirstShotDelay; //diff bet shot time and arrival time
	int killedTimeStep;  //Nader
	int firstshottime;  //the first time the enemy shot fire 
	int timeToShoot;
	
	
	//////////////END ADDITION//////
	//
	// TODO: Add More Data Members As Needed
	//

public:
	
	// added constructor
	
	Enemy(int id,int arrival, int EnemyHealth, int fire, int reload,int s,REGION r_region ,color r_c,int typ, int d = MaxDistance);
	Enemy();
	virtual ~Enemy();

	color GetColor() const; 
	REGION GetRegion() const;
	void setRegion(REGION r);
	virtual void DecrementDist(int)=0;

	void SetDistance(int d);
	int GetDistance()const ;

	/////////ADDED/////////
	void setspeed(int s);
	int getspeed();
	int getID() const; //Nader
	int getKilledTimeStep() const; //Nader
	void setKilledTimeStep(int currentTimeStep); //Nader
	int getFirstShotDelay() const; //Nader	
	int getKilledDelay() const; //Nader
	int getLifeTime() const; //Nader
	int getArrivalTime() const;
	void setFirePower( int fire);
	int getFirePower() const ;
	int getState() const;
	void setState(int s);
	void setHealth (int hlth);
	int getHealth ();
	int getType ();
	int ToShoot();
	bool operator==(const Enemy & enemy);
	bool operator==(const Enemy* & enemy);  // reham  overloading for enqueue function
	bool operator >(const Enemy* & rhs);    // reham  overloading for enqueue function
	bool operator < (const Enemy* & rhs);   // reham  overloading for enqueue function
	void setFirstShotDelay() ;  
	void setarrivaltime(int arrt);
	void setfirstshouttime(int fst);
	int getfirstshottime();
    virtual void DamageToEnemy(int TowerfirePow)=0;  //M//
	int gettimetoshoot();
	void decreaceTimeToShoot();

	


	/////END ADDITION//////
	// Virtual Functions: ----------------

	//virtual void Move() = 0;	    //All enemies can move
	//virtual void Attack() = 0;	//All enemies can attack (attacking is paving or shooting)

	//
	// TODO: Add More Member Functions As Needed
	//

};

