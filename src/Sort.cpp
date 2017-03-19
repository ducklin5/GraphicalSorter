#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>

//create a new type

//declare our function names
void printArray(std::vector<float> p);
void drawLines (std::vector<float> p);
void bubbleSort (std::vector<float>& p);
void bubble_sort(std::vector<float>& p);

int main()
{

	//create our array with 500 elements
	std::vector<float> array(20);

	//fill the array with random numbers from 0 to 299
	int seed = time(NULL);
	srand(seed);
	int n = array.size();
	for(int i = 0; i < n; i++){
		array[i] = rand()%300;
	};

	//print our array for clarity
	for( int i=0; i< n; ++i){
	  std::cout << array[i] << ' ';
	}
	std::cout << " : Array created" << std::endl;

	// Sort our Array of random numbers
	sf::Thread tSort(&bubbleSort, array);
	tSort.launch();
	sf::sleep(sf::seconds(2));
	// Draw our array of random numbers as lines
	sf::Thread tDrawLines(&drawLines, array);
	tDrawLines.launch();

}

//Draw any array of floating numbers as lines
void drawLines (std::vector<float> p){
	//create a window called Sort Algorithms
	//we will draw to this
	sf::RenderWindow window(sf::VideoMode(600, 600), "Sort Algorithms");

	//print the size of the input array for clarity
	int n = p.size();
	std::cout << n << std::endl;

	//make an array of rectangle with the same number of elements as the input array
	sf::RectangleShape rectangle[n];

	std::cout << n << std::endl;

	//set the starting position of each line

	for (int x = 0; x < n; x++ ){
		rectangle[x].setPosition(1, 1 + 3*x);
		std::cout << n << std::endl;
	}


	while (window.isOpen())
	{
		//clear window
		window.clear();
		//update the size of each line by checking the input array elemts
		for (int x = 0; x < n; x++ ){
			//if (rectangle[x].getSize() != sf::Vector2f(p[x], 1)){
				//std::cout << p[x] << ", " ;
				rectangle[x].setSize(sf::Vector2f(p[x], 1));
				//rectangle[x].setFillColor(sf::Color::Red);
			//}else if ( rectangle[x].getFillColor() != sf::Color::White ){
				rectangle[x].setFillColor(sf::Color::White);
			//}
			//redraw each triangle
			window.draw(rectangle[x]);
		}
		//std::cout << std::endl ;
		window.display();

		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
}


// Print any array of floating numbers
void printArray( std::vector<float> p ){
	int n = p.size();
	for (int i = 0; i < n - 1; i++) {
		std::cout << p[i] << ", ";
	}
	std::cout << p[p.size()-1] << std::endl;
}


// Create sort function >> not my code
//I added timers to each algorithm

void bubbleSort( std::vector<float> & p)
{
	sf::Clock clock;
	int n = p.size();
	for (int i = n-1; i > 0; i--){
		for (int j = 0; j < i; j++){
			//printArray( p );
			if (p[j] > p[j+1]){std::swap(p[j],p[j+1]);};
		}
	}
	printArray( p );
	sf::Time elps = clock.getElapsedTime();
	std::cout << "It took " << elps.asMilliseconds() << " msecs to sort." <<  std::endl;

}

void bubble_sort( std::vector<float> & p ) {
	sf::Clock clock;
	int n = p.size();
	for(int k = 0; k< n-1; k++) {
		// (p.size-k-1) is for ignoring comparisons of elements which have already been compared in earlier iterations

		for(int i = 0; i < n-k-1; i++) {
			//printArray( p );
			if(p[ i ] > p[ i+1] ) {
				// here swapping of positions is being done.
				std::swap(p[i],p[i+1]);
			}
		}
	}
	sf::Time elps = clock.getElapsedTime();
	std::cout << "It took " << elps.asMicroseconds() << " usecs to sort." <<  std::endl;
}
