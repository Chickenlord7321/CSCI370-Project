#include "../Crow/include/crow.h"
#include <iostream>
	using namespace std;

int main()
{
	// Init Crow app
	crow::SimpleApp app;

	// Endpoint for root
	CROW_ROUTE(app, "/")([](){
		auto page  = crow::mustache::load_text("index.html");
		return page;
	});

	// Endpoint for greeting
	CROW_ROUTE(app, "/<string>")([](string name){
		auto page = crow::mustache::load("index.html");
		// Context contains the "person" variable for our template page 
		// and the `name` variable we get from the URL
		crow::mustache::context ctx ({{"person", name}});
        return page.render(ctx);
	});

	// Set port and tell the app to run on multiple threads.
	// Also runs the app
	app.port(18080).multithreaded().run();
}