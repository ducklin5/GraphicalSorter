#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>

//create a new type
struct ArraynSize{
	int size;
	float* set;
};

//declare our function names
void printArray( struct ArraynSize );
void swap(float& x, float& y);
void bubbleSort (struct ArraynSize );
void drawLines (struct ArraynSize);
void bubble_sort( struct ArraynSize p);



int main()
{

	//Create an ArraynSize object
	//which holds the array of random numbers and the size of said array
	//this is needed to use sf::Thread for multi-threading
	struct ArraynSize Param;
	Param.size = 200;
	float a[Param.size];
	Param.set = a;
	//create an array with random numbers
	int seed = time(NULL);
	srand(seed);
	for(int i = 0; i < Param.size; i++){
		Param.set[i] = rand()%300;
	};


	// Draw our array of random numbers as lines
	sf::Thread tDrawLines(&drawLines,Param);
	sf::Thread tSort(&bubble_sort,Param);

	tDrawLines.launch();
	sf::sleep(sf::seconds(2));
	// Sort our Array of random numbers
	tSort.launch();
	return 0;
}

//Draw any array of floating numbers as lines
void drawLines (struct ArraynSize p){
	//create a window called Sort Algorithms
	//we will draw to this
	sf::Window window(sf::VideoMode(600, 600), "Sort Algorithms");
	//make an array of rectangle with the same number of elements as the input array
	sf::RectangleShape rectangle[p.size];
	for (int x = 0; x < p.size; x++ )
		rectangle[x].setPosition(1, 1 + x);

	while (window.isOpen())
	{
		window.clear();
		for (int x = 0; x < p.size; x++ ){
			if (rectangle[x].getSize() != sf::Vector2f(p.set[x], 1)){
				rectangle[x].setSize(sf::Vector2f(p.set[x], 1));
				rectangle[x].setFillColor(sf::Color::Red);
			}else if ( rectangle[x].getFillColor() != sf::Color::White ){
				rectangle[x].setFillColor(sf::Color::White);
			}
			window.draw(rectangle[x]);
		}
		window.display();

		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
	}
}


// Print any array of floating numbers
void printArray( struct ArraynSize p )
{
	for (int i = 0; i < p.size - 1; i++) {
		std::cout << p.set[i] << ", ";
	}
	std::cout << p.set[p.size-1] << std::endl;
}


// Create sort function (with assisting swap function) >> not my code
void swap(float& x, float& y)
{
	float temp = x;
	x = y;
	y = temp;
}

void bubbleSort( struct ArraynSize p)
{
	sf::Clock clock;
	for (int i = p.size-1; i > 0; i--){
		for (int j = 0; j < i; j++){
			//printArray( p );
			if (p.set[j] > p.set[j+1]){swap(p.set[j],p.set[j+1]);};
		}
	}
	sf::Time elps = clock.getElapsedTime();
	std::cout << "It took " << elps.asMilliseconds() << " msecs to sort." <<  std::endl;
}

void bubble_sort( struct ArraynSize p ) {
	sf::Clock clock;
	for(int k = 0; k< p.size-1; k++) {
          // (p.size-k-1) is for ignoring comparisons of elements which have already been compared in earlier iterations

          for(int i = 0; i < p.size-k-1; i++) {
        	  printArray( p );
                 if(p.set[ i ] > p.set[ i+1] ) {
                      // here swapping of positions is being done.
                	 swap(p.set[i],p.set[i+1]);
                  }
          }
    }
	sf::Time elps = clock.getElapsedTime();
	std::cout << "It took " << elps.asMicroseconds() << " usecs to sort." <<  std::endl;
}
