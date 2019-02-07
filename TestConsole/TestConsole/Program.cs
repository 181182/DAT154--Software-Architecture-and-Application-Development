using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.IO;
using TestDoc;

namespace TestConsole
{
	class Program
	{
		public static void Main()
		{
			ArrayList a = new ArrayList();
			ArrayList planets = new ArrayList();
			ArrayList Earthmoons = new ArrayList();
			ArrayList Marsmoons = new ArrayList();
			ArrayList Jupitermoons = new ArrayList();
			ArrayList Saturnmoons = new ArrayList();
			ArrayList Uranusmoons = new ArrayList();
			ArrayList Neptunemoons = new ArrayList();
			ArrayList Plutomoons = new ArrayList();





			using (var reader = new StreamReader(@"Z:\deadmaggi On My Mac\Dat154\Planeter.csv"))
			{
				while (!reader.EndOfStream)
				{
					var line = reader.ReadLine();
					var values = line.Split(';');
					if (values[1].Equals("None"))
					{
						a.Add(new Star(values[0], Convert.ToDouble(values[2]), Convert.ToDouble(values[3]), Convert.ToDouble(values[4]), Convert.ToDouble(values[5]), "red"));
					}
					if (values[1].Equals("Sun"))
					{
						a.Add(new Planet(values[0], Convert.ToDouble(values[2]), Convert.ToDouble(values[3]), Convert.ToDouble(values[4]), Convert.ToDouble(values[5]), "red"));
						planets.Add(new Planet(values[0], Convert.ToDouble(values[2]), Convert.ToDouble(values[3]), Convert.ToDouble(values[4]), Convert.ToDouble(values[5]), "red"));
					}
					else
					{
						switch (values[1])
						{
							case "Earth":
								Earthmoons.Add(new Moon(values[0], Convert.ToDouble(values[2]), Convert.ToDouble(values[3]), Convert.ToDouble(values[4]), Convert.ToDouble(values[5]), "red"));
								break;
							case "Mars":
								Marsmoons.Add(new Moon(values[0], Convert.ToDouble(values[2]), Convert.ToDouble(values[3]), Convert.ToDouble(values[4]), Convert.ToDouble(values[5]), "red"));
								break;
							case "Jupiter":
								Jupitermoons.Add(new Moon(values[0], Convert.ToDouble(values[2]), Convert.ToDouble(values[3]), Convert.ToDouble(values[4]), Convert.ToDouble(values[5]), "red"));
								break;
							case "Saturn":
								Saturnmoons.Add(new Moon(values[0], Convert.ToDouble(values[2]), Convert.ToDouble(values[3]), Convert.ToDouble(values[4]), Convert.ToDouble(values[5]), "red"));
								break;
							case "Uranus":
								Uranusmoons.Add(new Moon(values[0], Convert.ToDouble(values[2]), Convert.ToDouble(values[3]), Convert.ToDouble(values[4]), Convert.ToDouble(values[5]), "red"));
								break;
							case "Neptune":
								Neptunemoons.Add(new Moon(values[0], Convert.ToDouble(values[2]), Convert.ToDouble(values[3]), Convert.ToDouble(values[4]), Convert.ToDouble(values[5]), "red"));
								break;
							case "Pluto":
								Plutomoons.Add(new Moon(values[0], Convert.ToDouble(values[2]), Convert.ToDouble(values[3]), Convert.ToDouble(values[4]), Convert.ToDouble(values[5]), "red"));
								break;
						}
					}

				}
			}

			for (int i = 0; i < a.Count; i++)
			{
				SpaceObject obj = (SpaceObject)(a[i]);
				if (obj.name.Equals("Sun"))
				{
					obj.planets = planets;
					goto ferdig;
				}

			}
			ferdig:

			for (int i = 0; i < a.Count; i++)
			{
				SpaceObject obj = (SpaceObject)(a[i]);
				switch (obj.name)
				{
					case "Earth":
						obj.moons = Earthmoons;
						break;
					case "Mars":
						obj.moons = Marsmoons;
						break;
					case "Jupiter":
						obj.moons = Jupitermoons;
						break;
					case "Saturn":
						obj.moons = Saturnmoons;
						break;
					case "Uranus":
						obj.moons = Uranusmoons;
						break;
					case "Neptune":
						obj.moons = Neptunemoons;
						break;
					case "Pluto":
						obj.moons = Plutomoons;
						break;
				}

			}
			Console.WriteLine("Skriv inn ønsket planet");
			string input = Console.ReadLine();
			Console.WriteLine("Skriv inn ønsket tid");
			int tid = Convert.ToInt32(Console.ReadLine());

			for (int i = 0; i < a.Count; i++)
			{
				SpaceObject obj = (SpaceObject)(a[i]);
				if (obj.name.Equals(input) && input != "Sun")
				{
					{
						obj.Draw();
						obj.Position(tid);
						ArrayList moons = obj.moons;
						for (int j = 0; j < moons.Count; j++)
						{
							SpaceObject moon = (SpaceObject)(moons[j]);
							moon.Draw();
							moon.Position(tid);
						}
						goto ferdig2;
					}
				}
				if (obj.name.Equals("Sun") && input.Equals("") || obj.name.Equals("Sun") && input.Equals("Sun"))
				{
					{
						obj.Draw();
						obj.Position(tid);
						ArrayList planeter = obj.planets;
						for (int j = 0; j < planeter.Count; j++)
						{
							SpaceObject planet = (SpaceObject)(planeter[j]); planet.Draw(); planet.Position(tid);
						}
						goto ferdig2;
					}
				}
			}

			ferdig2:
			
			Console.ReadLine();
		}
	}
}
