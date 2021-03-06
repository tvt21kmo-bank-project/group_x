const express = require('express');
const router = express.Router();
const user = require('../models/user_model');

router.get('/:id?',
  function (request, response) {
    if (request.params.id) {
      user.getById(request.params.id, function (err, dbResult) {
        if (err) {
          response.json(err);
        } else {
          //response.json(dbResult);
          //response.json(dbResult[0].username);
          response.send(dbResult[0].username);
        }
      });
    } else {
      user.get(function (err, dbResult) {
        if (err) {
          response.json(err);
        } else {
          response.json(dbResult);
        }
      });
    }
  });
router.post('/',
  function (request, response) {
    user.add(request.body, function (err, count) {
      if (err) {
        response.json(err);
      } else {
        response.json(request.body);
      }
    });
  });

router.delete('/:id',
  function (request, response) {
    user.delete(request.params.id, function (err, count) {
      if (err) {
        response.json(err);
      } else {
        response.json(count);
      }
    });
  });


router.put('/:id',
  function (request, response) {
    user.update(request.params.id, request.body, function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult);
      }
    });
  });

router.get('/userid/:uname',
  function (request, response) {
    user.getUserId(request.params.uname, function (err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult[0].id_user);
      }
    });
  });

module.exports = router;