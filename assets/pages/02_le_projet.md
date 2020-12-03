<head>
  <meta charset="utf-8" />
  
  <style>
    .button {
      border: none;
      color: white;
      border-radius: 10px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 16px;
      transition-duration: 1s;
      cursor: pointer;
    }
    .button1 {
      background-color: white; 
      color: #165A97;
      padding: 16px 49px;
      border: 2px solid #165A97;
    }
    .button1:hover {
      background-color: #165A97;
      color: white;
    }
    .button2 {
      background-color: white; 
      color: #159758;
      padding: 16px 12px;
      border: 2px solid #159758;
    }
    .button2:hover {
      background-color: #159758;
      color: white;
    }
    .timeline {
      position: relative;
      max-width: 1200px;
      margin: 0 auto;
    }
    .timeline::after {
      content: '';
      position: absolute;
      width: 6px;
      background-color: #165A97;
      top: 0;
      bottom: 0;
      left: 50%;
      margin-left: -3px;
    }
    .container {
      padding: 10px 40px;
      position: relative;
      background-color: inherit;
      width: 50%;
    }
    .container::after {
        content: '';
        position: absolute;
        width: 25px;
        height: 25px;
        right: -17px;
        background-color: white;
        border: 4px solid #159758;
        top: 15px;
        border-radius: 50%;
        z-index: 1;
    }
    .left {
      left: 0;
    }
    .right {
      left: 50%;
    }
    .left::before {
      content: " ";
      height: 0;
      position: absolute;
      top: 22px;
      width: 0;
      z-index: 1;
      right: 30px;
      border: medium solid #E8EEF4;
      border-width: 10px 0 10px 10px;
      border-color: transparent transparent transparent #E8EEF4;
    }
    .right::before {
      content: " ";
      height: 0;
      position: absolute;
      top: 22px;
      width: 0;
      z-index: 1;
      left: 30px;
      border: medium solid #E8EEF4;
      border-width: 10px 10px 10px 0;
      border-color: transparent #E8EEF4 transparent transparent;
    }
    .right::after {
      left: -16px;
    }
    .content {
      padding: 20px 30px;
      background-color: #E8EEF4;
      position: relative;
      border-radius: 6px;
    }
  </style>

</head>


## RéponsAtout, qu'est-ce donc ?

* * *


### Le contexte
>Actuellement en 2ème année d'école d'ingénieur en systèmes embraqués et communicants, à **l'ISEN de Toulon** et en apprentissage avec **l'ITII**. Nous avons réalisé le projet RéponsAtout afin de mettre en pratique les cours de système d'exploitation. 

### Le produit
>De nos jours, le technologie est omniprésente. On la retrouve de partout sous différentes formes, notamment chez nous, cela va de notre ordianteur, téléphone à des technologies bien plus poussées.
>
>C'est le cas de RéponsAtout, c'est un serveur vous permettant de répondre à vos questions. Mais qu'a t'il de mieux que les autres ?
>
>C'est tout simple, il agit dès que vous lui demandiez, vous n'avez pas besoin de relancer le serveur à chaque fois que vous en avez besoin. De plus, tout le monde peut l'utiliser, beaucoup de serveurs fonctionnent oralement sans penser aux personnes malentendantes, RéponsAtout s'utilise grâce à une interface.

<p>&nbsp;</p>

## Les moments forts

* * *

<div class="timeline">
  <div class="container left">
    <div class="content">
      <h3>19 Novembre 2020</h3>
      <p>Premier rendez-vous avec le client afin de déterminer ses besoins. Définiton des rôles de chaque membres du groupe et début des recherches.</p>
    </div>
  </div>
  <div class="container right">
    <div class="content">
      <h3>02 Décembre 2020</h3>
      <p>Daily meeting avec le client qui est sastifait de notre avancement. Le client peut poser plusieurs questions précisent au serveur et obtenir des réponses.</p>
      <p>La proposition de rajouter une question dynamique (réponse en temps réel), a été accepté mais on ne réalise pas de multiprocesseurs.</p>
    </div>
  </div>
  <div class="container left">
    <div class="content">
      <h3>03 Décembre 2020</h3>
      <p>La majorité des demandes du client ont été réalisé, nous avons décidé d'essayer d'utiliser un Raspberry Pi afin d'y mettre notre serveur RéponsAtout</p>
    </div>
  </div>
</div>

<p>&nbsp;</p>

## Documents téléchargables

* * *

*   Vous pouvez récupérer notre programme en téléchargent ses deux fichiers : <a href="../code/pere.c" download>1er fichier</a> et <a href="../code/fils.c" download>2ème fichier</a>
<p>&nbsp;</p>
<p>&nbsp;</p>

<button class="button button1" onclick="window.location.href = 'https://eva-joly.github.io/ReponsAtout/';">Home</button>
<button class="button button2" style="float:right" onclick="window.location.href = 'https://eva-joly.github.io/ReponsAtout/assets/pages/01_nous_connaitre';">Nous connaitres</button>
