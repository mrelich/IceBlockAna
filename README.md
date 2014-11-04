IceBlockAna
===========

New analysis framework that will clean up IceBlock working Area.

The goal will be to have a root file containing several things:
1.) Meta data about the run so I can easily check back in the
    future
2.) Tree that contains all the event information.  In this case
    it will be the raw vector potential for each antenna stored
    inside a TProfile.
3.) Summary information such as: average vector potential and 
    the average electric field derived from the vector potential.

