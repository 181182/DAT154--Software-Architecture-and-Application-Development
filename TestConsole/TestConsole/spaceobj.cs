using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace TestDoc
{

    public class SpaceObject
    {

        public String name { get; set; }
        public double orbital_radius { get; set; }
        public double orbital_period { get; set; }
        public double object_radius { get; set; }
        public double rotational_period { get; set; }
        public String color { get; set; }
        public ArrayList planets { get; internal set; }
        public ArrayList moons { get; internal set; }

        public SpaceObject(String _name, double _orbital_radius, double _orbital_period, double _object_radius, double _rotational_period, String _color)
        {
            name = _name;
            orbital_radius = _orbital_radius;
            orbital_period = _orbital_period;
            object_radius = _object_radius;
            rotational_period = _rotational_period;
            color = _color;
        }

        public virtual void Position(double time)
        {
            if (this.orbital_period != 0)
            {
                double degreeRAD = (((360 / this.orbital_period) * time) * Math.PI) / 180;
                double x = this.orbital_radius * Math.Cos(degreeRAD);
                double y = this.orbital_radius * Math.Sin(degreeRAD);


                Console.WriteLine("position is : " + x + "," + y + " degrees");
            }
            else Console.WriteLine("position is: 0,0");

        }
        public virtual void Draw()
        {
            Console.WriteLine(name);
        }
    }

    public class Star : SpaceObject
    {
        public Star(String _name, double _orbital_radius, double _orbital_period, double _object_radius, double _rotational_period, String _color) : base(_name, _orbital_radius, _orbital_radius, _object_radius, _rotational_period, _color) { }

        public override void Position(double time)
        {
            base.Position(time);
        }
        public override void Draw()
        {
            Console.Write("Star : ");
            base.Draw();
        }
        public ArrayList planets { get; set; }

    }

    public class Planet : SpaceObject
    {
        public Planet(String _name, double _orbital_radius, double _orbital_period, double _object_radius, double _rotational_period, String _color) : base(_name, _orbital_radius, _orbital_radius, _object_radius, _rotational_period, _color) { }

        public override void Position(double time)
        {
            base.Position(time);
        }
        public override void Draw()
        {
            Console.Write("Planet: ");
            base.Draw();
        }
        //private Moon[] moons = new Moon[30];
        public ArrayList moons { get; set; }

    }
    public class Moon : SpaceObject
    {
        public Moon(String _name, double _orbital_radius, double _orbital_period, double _object_radius, double _rotational_period, String _color) : base(_name, _orbital_radius, _orbital_radius, _object_radius, _rotational_period, _color) { }
        public override void Position(double time)
        {
            base.Position(time);
        }
        public override void Draw()
        {
            Console.Write("Moon : ");
            base.Draw();
        }
    }
    public class Dwarf_Planet : Planet
    {
        public Dwarf_Planet(String _name, double _orbital_radius, double _orbital_period, double _object_radius, double _rotational_period, String _color) : base(_name, _orbital_radius, _orbital_radius, _object_radius, _rotational_period, _color) { }

        public override void Position(double time)
        {
            base.Position(time);
        }
        public override void Draw()
        {
            Console.Write("Dwarf Planet: ");
            base.Draw();
        }
    }
    public class Asteroid : SpaceObject
    {
        public Asteroid(String _name, double _orbital_radius, double _orbital_period, double _object_radius, double _rotational_period, String _color) : base(_name, _orbital_radius, _orbital_radius, _object_radius, _rotational_period, _color) { }

        public override void Position(double time)
        {
            base.Position(time);
        }
        public override void Draw()
        {
            Console.Write("Asteroids : ");
            base.Draw();
        }
    }
    public class Asteroid_belt : Asteroid
    {
        public Asteroid_belt(String _name, double _orbital_radius, double _orbital_period, double _object_radius, double _rotational_period, String _color) : base(_name, _orbital_radius, _orbital_radius, _object_radius, _rotational_period, _color) { }

        public override void Position(double time)
        {
            base.Position(time);
        }
        public override void Draw()
        {
            Console.Write("Asteroid belt : ");
            base.Draw();
        }
    }
    public class Comet : SpaceObject
    {
        public Comet(String _name, double _orbital_radius, double _orbital_period, double _object_radius, double _rotational_period, String _color) : base(_name, _orbital_radius, _orbital_radius, _object_radius, _rotational_period, _color) { }

        public override void Position(double time)
        {
            base.Position(time);
        }
        public override void Draw()
        {
            Console.Write("Comet : ");
            base.Draw();
        }
    }



}
