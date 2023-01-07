#include <stdio.h>
#include <wpsapi.h>

int main(int argc, char** argv) {
    int rc = WPS_load();
    if (rc != WPS_OK) {
        fprintf(stderr, "WPS_load failed (%d)\n", rc);
        return rc;
    }

    WPS_set_key("YOUR KEY");  // replace with your API key!

    WPS_Location* location;
    rc = WPS_location(NULL, WPS_NO_STREET_ADDRESS_LOOKUP, &location);
    if (rc == WPS_OK) {
        printf("%.6f, %.6f +/-%.1fm\n", location->latitude, location->longitude, location->hpe);
        // could fall back here to WPS_ip_location to get a coarse location
    } else {
        fprintf(stderr, "WPS_location failed (%d)\n", rc);
    }

    WPS_unload();
    return 0;
}
