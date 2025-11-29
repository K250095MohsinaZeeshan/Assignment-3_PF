#include <stdio.h>

int calculateFuel(int fuel, int consumption, int recharge,int solarBonus, int planet, int totalPlanets)
{
    if (fuel <= 0) 
	{
        printf("\nFuel exhausted! Mission failed.\n");
        return 0;
    }
    if (planet > totalPlanets) 
	
	{
        printf("\nAll planets visited! Mission successful\n");
        return 1;
    }
    fuel -= consumption;

    if (planet % 2 == 0)
          fuel += recharge;
    if (planet % 4 == 0)
          fuel += solarBonus;
    printf("\nPlanet %d: Fuel Remaining = %d\n", planet, fuel);
         return calculateFuel(fuel, consumption, recharge, solarBonus,planet + 1, totalPlanets);
}
int main() 
{
    int fuel, consumption, recharge, solarBonus, totalPlanets;
    printf("SPACE SIMULATION\n");
    printf("________________\n");
	
	printf("\nEnter initial fuel: ");
    scanf("%d", &fuel);

    printf("Enter fuel consumption per planet: ");
    scanf("%d", &consumption);

    printf("Enter fuel recharge in gravity zones: ");
    scanf("%d", &recharge);

    printf("Enter solar bonus (every 4 planets): ");
    scanf("%d", &solarBonus);

    printf("Enter total number of planets: ");
    scanf("%d", &totalPlanets);
    calculateFuel(fuel, consumption, recharge, solarBonus, 1, totalPlanets);
    return 0;
}

