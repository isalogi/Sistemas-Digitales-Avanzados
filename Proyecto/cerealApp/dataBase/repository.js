var MongoClient = require('mongodb').MongoClient;
var assert = require('assert');

const url = 'mongodb://localhost:27017';
const dbName = 'CerealD';

const client = new MongoClient(url);

class Repository {

    constructor() {

    }

    insertAlert(alert,onSucess) {

        // Use connect method to connect to the Server
        client.connect(function (err) {
            assert.equal(null, err);
            console.log("Connected successfully to server");

            const db = client.db(dbName);

            const collection = db.collection('alerts');
            // Insert some documents
            collection.insertMany([alert], function (err, result) {
                assert.equal(err, null);
                assert.equal(1, result.result.n);
                assert.equal(1, result.ops.length);
                console.log("Inserted 1 alert into the collection");
                onSucess(result);
            });

            client.close();

        });

    }

    findAlert(onSucess) {

        // Use connect method to connect to the Server
        client.connect(function (err) {
            assert.equal(null, err);
            console.log("Connected successfully to server");

            const db = client.db(dbName);

            const collection = db.collection('alerts');

            collection.find({}).toArray(function (err, docs) {
                assert.equal(err, null);
                console.log("Found the following records");
                console.log(docs)

                onSucess(docs);
            });

            client.close();

        });

    }

}

module.exports = Repository


