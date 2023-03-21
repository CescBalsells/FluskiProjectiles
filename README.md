# FluskiProjectiles
 
 The Plug-in includes the FluskiProjectileMovementComponent and the 5 Projectile Actors.
 
 ![FluskiProjectilesPlugin](https://user-images.githubusercontent.com/45798069/226667933-d7fa6bb9-52dd-44cd-953e-ef551683b5f9.PNG)
 
 ## FluskiProjectileMovementComponent
 This Movement Component inherits from the Unreal ProjectileMovementComponent and adds some extra features:
 
 1. Charged Speed: The Initial Speed of the projectile is determined by how charged is the projectile. Being 1 max speed and 0 min speed.
 2. Distance: Broadcast an event when the projectile reached certain distance.
 3. HominDistance: If the Projectile has a HomingTarget only will be applied when the projectile is inside the determined distance range from it's target.
 
Unlike the normal ProjectileMovementComponent this one has to be thrown using the function ThrowProjectile, without using this function the projectile will not start moving.
 
 ## Projectiles
 
 The plugin also includes diferent type of projectiles listed below:
 
 1. BaseProjectile
 2. DamageProjectile
 3. ChargedProjectile
 4. ExplosiveProjectile
 5. GrenadeProecjtile
 
 ### BaseProjectile
 
 ### DamageProjectile
 
 ### ChargedProjectile
 
 ### ExplosiveProjectile
 
 ### GrenadeProecjtile
 



