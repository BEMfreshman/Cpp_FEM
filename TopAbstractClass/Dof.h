#ifndef __DOF_H__
#define __DOF_H__

class DofManager;

class DOF
{
public:
	DOF();
	DOF(int id, DofManager* DM);

	int getid() const;
	DofManager* getDM() const;

	virtual ~DOF();

private:
	int id;

	DofManager* DM;    //¸ÃDOFÊôÓÚÄÄ¸öDofManager

};

#endif