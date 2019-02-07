#pragma once
class Car
{
public:
	Car(int bilId);
	Car(const Car &car);
	~Car();


	int getId();
	int getRetning();
	int getTop();
	int getLeft();
	int getRight();
	int getBottom();

	void setTop(int t);
	void setLeft(int l);
	void setRight(int r);
	void setBottom(int b);
	void setRetning(int r);

	bool operator==(Car &car1) const;
	friend bool operator == (Car const &car1, Car const &car2);

private:
	int id;
	int top;
	int left;
	int right;
	int bottom;
	int retning;
};

