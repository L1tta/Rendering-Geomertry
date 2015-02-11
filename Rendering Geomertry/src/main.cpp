#include <iostream>
#include "Gizmos.h"
#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"
#include "ProjectApp.h"
int main()
{
	ProjectApp* App = new ProjectApp();
	if (App->Startup() == true)
	{
		while (App->Update() == true)
		{
			App->Draw();
		}

		App->Shutdown();
	}
	delete App;
	return 0;
}