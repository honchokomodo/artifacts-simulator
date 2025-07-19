#include "artifact.c"
#include <time.h>

int main(void)
{
	srand(time(NULL));

	Artifact newartifact = artifact_new_domain();
	artifact_print(newartifact);

	newartifact = artifact_upgrade(newartifact);
	newartifact = artifact_upgrade(newartifact);
	newartifact = artifact_upgrade(newartifact);
	newartifact = artifact_upgrade(newartifact);
	newartifact = artifact_upgrade(newartifact);
	artifact_print(newartifact);

	return 0;
}
