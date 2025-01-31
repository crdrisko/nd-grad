molecule
{
  name = "SPCE";

  atom[0]
  {
    type = "O_SPCE";
    position( 0.0, 0.0, -0.06461 );
  }
  atom[1]
  {
    type = "H_SPCE";
    position( 0.0, 0.81649, 0.51275 );
  }
  atom[2]
  {
    type = "H_SPCE";
    position( 0.0, -0.81649, 0.51275 );
  }

  rigidBody[0]
  {
    members(0, 1, 2);
  }
}

molecule
{
  name = "Ca2+";

  atom[0]
  {
    type = "Ca2+";
    position(0.0, 0.0, 0.0);
  }
}

molecule
{
  name = "Cl-";

  atom[0]
  {
    type = "Cl-";
    position(0.0, 0.0, 0.0);
  }
}
