#ifndef ARTIFACT_UI_C
#define ARTIFACT_UI_C

#include "artifact.c"
#include "components.c"

typedef void (*ArtifactUIFunc)(ArtifactLoadout *);
void noop_artifact_ui_func(ArtifactLoadout * in)
{
	// this function does nothing
}

#define TEMPLATE_set2ui_impl
#include "artifacts/artifacts_list.h"
#undef TEMPLATE_set2ui_impl

ArtifactUIFunc const set2ui[] = {
	[SET_NOTHING] = noop_artifact_ui_func,
#define TEMPLATE_set2ui_arr
#include "artifacts/artifacts_list.h"
#undef TEMPLATE_set2ui_arr
};

#endif
